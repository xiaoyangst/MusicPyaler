/**
  ******************************************************************************
  * @file           : MusicPlayer.h
  * @author         : xy
  * @brief          : None
  * @attention      : None
  * @date           : 2024-07-14
  ******************************************************************************
  */

#ifndef MUSICPLAYER__MUSICPLAYER_H_
#define MUSICPLAYER__MUSICPLAYER_H_

#include <QMediaPlayer>

class MusicPlayer : public QMediaPlayer{

  Q_OBJECT

 public:
  explicit MusicPlayer(QObject *parent = nullptr);
 private:

};

#endif //MUSICPLAYER__MUSICPLAYER_H_
