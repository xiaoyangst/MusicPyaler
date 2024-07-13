#include <QApplication>
#include "musicwindow.h"


int main(int argc, char *argv[]) {

  QApplication a(argc, argv);

  MusicWindow main_widget;
  main_widget.show();

  return QApplication::exec();
}