//
// Created by xy on 2024-07-10.
//

// You may need to build the project (run Qt uic code generator) to get "ui_MusicWindow.h" resolved

#include "musicwindow.h"
#include "ui_MusicWindow.h"

MusicWindow::MusicWindow(QWidget *parent) :
    QWidget(parent), ui(new Ui::MusicWindow) {
  ui->setupUi(this);
}

MusicWindow::~MusicWindow() {
  delete ui;
}
