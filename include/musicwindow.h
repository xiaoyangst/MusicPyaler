//
// Created by xy on 2024-07-10.
//

#ifndef MUSICPLAYER__MUSICWINDOW_H_
#define MUSICPLAYER__MUSICWINDOW_H_

#include <QWidget>

QT_BEGIN_NAMESPACE
namespace Ui { class MusicWindow; }
QT_END_NAMESPACE

class MusicWindow : public QWidget {
 Q_OBJECT

 public:
  explicit MusicWindow(QWidget *parent = nullptr);
  ~MusicWindow() override;

 private:
  Ui::MusicWindow *ui;
};

#endif //MUSICPLAYER__MUSICWINDOW_H_