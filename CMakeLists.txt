cmake_minimum_required(VERSION 3.26)
project(MusicPlayer)

set(CMAKE_CXX_STANDARD 17)


set(CMAKE_PREFIX_PATH "C:/Qt/6.5.3/mingw_64")

set(CMAKE_INCLUDE_CURRENT_DIR ON)

find_package(Qt6 COMPONENTS
        Core
        Gui
        Widgets
        Network
        Multimedia
        REQUIRED)

#搜索头文件
include_directories(include/)
file(GLOB HEADER_FILES "include/*.h")

#搜索源文件
file(GLOB SRC_LIST "src/*.cpp")

# 搜索ui文件
file(GLOB UI_FILES "ui/*.ui")

# 搜索资源文件（图片、图标、音乐等）
file(GLOB_RECURSE RESOURCES "sources/*.qrc")

add_subdirectory(src)

# 生成头文件的 MOC 文件
QT6_WRAP_CPP(HEADERS_MOC ${HEADER_FILES})
# 生成 UI 文件对应的头文件
QT6_WRAP_UI(FORMS_HEADERS ${UI_FILES})
# 添加资源文件
QT6_ADD_RESOURCES(RCC ${RESOURCES})



add_executable(MusicPlayer main.cpp ${HEADERS_MOC} ${SRC_LIST} ${FORMS_HEADERS} ${RCC})
target_link_libraries(MusicPlayer
        Qt6::Core
        Qt6::Gui
        Qt6::Widgets
        Qt6::Network
        Qt6::Multimedia
)

