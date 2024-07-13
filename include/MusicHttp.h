/**
  ******************************************************************************
  * @file           : MusicHttp.h
  * @author         : xy
  * @brief          : None
  * @attention      : None
  * @date           : 2024-07-12
  ******************************************************************************
  */

#ifndef MUSICPLAYER__MUSICHTTP_H_
#define MUSICPLAYER__MUSICHTTP_H_

#include <QObject>
#include <QNetworkAccessManager>
#include <QNetworkReply>

class MusicHttp : public QObject{
  Q_OBJECT

 public:
  enum MusicHttpState{
    MusicHttpErrorState = 0,
    MusicHttpSuccessState
  };

  explicit MusicHttp(const QString &filename,QObject *parent = nullptr);
  ~MusicHttp();
  void get(const QString &httpUrl);
  bool isError();
  QByteArray readAll();
 public slots:
  void readData();
 void handleError(QNetworkReply::NetworkError code);
 void handleFinished();
signals:
  void finishedRead();
 private:
  enum MusicHttpState state_;
  QString filename_;
  QNetworkAccessManager *manager_;
};

#endif //MUSICPLAYER__MUSICHTTP_H_
