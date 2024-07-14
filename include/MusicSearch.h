/**
  ******************************************************************************
  * @file           : MusicSearch.h
  * @author         : xy
  * @brief          : None
  * @attention      : None
  * @date           : 2024-07-13
  ******************************************************************************
  */

#ifndef MUSICPLAYER__MUSICSEARCH_H_
#define MUSICPLAYER__MUSICSEARCH_H_

#include <QObject>
#include <QJsonDocument>
#include <QJsonParseError>
#include <QJsonObject>
#include <QJsonArray>


#include "MusicHttp.h"

class MusicSearch : public QObject{
  Q_OBJECT
 public:
  explicit MusicSearch(QObject *parent = nullptr);
  void search(const QString &music);
  void parseMusicJsonData(const QByteArray &jsonData);
  void setHttpWeb(QString ip,int port);
  QString getHttpWeb();
 public slots:
  void handleData();
 signals:
  void ToNetTable(QJsonArray data);
 private:
  MusicHttp *http_;
  QString httpUrl_;
};

#endif //MUSICPLAYER__MUSICSEARCH_H_
