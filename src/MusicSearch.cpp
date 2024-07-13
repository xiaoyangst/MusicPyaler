#include "MusicSearch.h"
#include <QJsonDocument>
#include <QJsonParseError>
#include <QJsonObject>
#include <QJsonArray>

MusicSearch::MusicSearch(QObject *parent) : QObject(parent) {
  http_ = new MusicHttp("music.json", this);

  connect(http_,&MusicHttp::finishedRead, this,&MusicSearch::handleData);
}
void MusicSearch::search(const QString &music) {
  QString httpUrl = QString("http://192.168.56.1:80/music/music.json");
  http_->get(httpUrl);
}
void MusicSearch::handleData() {
  QByteArray data = http_->readAll();
  parseMusicJsonData(data);
}
void MusicSearch::parseMusicJsonData(const QByteArray &jsonData) {
  QJsonParseError jsonParseError;
  QJsonDocument musicDocument = QJsonDocument::fromJson(jsonData,&jsonParseError);
  if (musicDocument.isEmpty()){
    qDebug()<<"Fail to parse json data:"<<jsonParseError.errorString();
    return;
  }
  QJsonObject musicObject = musicDocument.object();
  QJsonArray musicArray = musicObject["list"].toArray();
  for (int i = 0; i < musicArray.size(); i++) {
    QJsonObject object = musicArray[i].toObject();
    QString musicName = object["musicName"].toString();
    QString albumName = object["albumName"].toString();
    qint32 MusicDuration = object["duration"].toInt();
    QString musicMp3 = object["mp3"].toString();
    QString MusicLrc = object["lrc"].toString();
    QString MusicImg = object["img"].toString();

    qDebug()<<"musicName = "<<musicName;
    qDebug()<<"albumName = "<<albumName;
    qDebug()<<"MusicDuration = "<<MusicDuration;
    qDebug()<<"musicMp3 = "<<musicMp3;
    qDebug()<<"MusicLrc = "<<MusicLrc;
    qDebug()<<"MusicImg = "<<MusicImg;
  }
}
















