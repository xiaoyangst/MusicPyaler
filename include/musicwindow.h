//
// Created by xy on 2024-07-10.
//

#ifndef MUSICPLAYER__MUSICWINDOW_H_
#define MUSICPLAYER__MUSICWINDOW_H_

#include <QWidget>
#include <QJsonArray>
#include <QJsonObject>
#include <QMediaPlayer>

#include "MusicSearch.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MusicWindow; }
QT_END_NAMESPACE

class MusicWindow : public QWidget {
 Q_OBJECT

 public:
  explicit MusicWindow(QWidget *parent = nullptr);
  ~MusicWindow() override;
 private:
  void initQTableWidget();
  void playMusic(const QStringList &urlList);
 public slots:
  void searchMusic();
  void showNetToTable(QJsonArray data);
  void playNetMusic(int row, int column);
  void updateDurationChanged(qint64 duration);
  void updatePositionChanged(qint64 position);
  void updateSliderMoved(int position);
 private:
  Ui::MusicWindow *ui;
  MusicSearch* musicSearch_;
  QMediaPlayer* musicPlayer_;
  QAudioOutput* audioOutput_;
};

#endif //MUSICPLAYER__MUSICWINDOW_H_
