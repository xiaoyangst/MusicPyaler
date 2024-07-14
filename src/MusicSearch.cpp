
#include "MusicSearch.h"

MusicSearch::MusicSearch(QObject *parent) : QObject(parent) {
  setHttpWeb("192.168.56.1",80);
  http_ = new MusicHttp("music.json", this);

  connect(http_,&MusicHttp::finishedRead, this,&MusicSearch::handleData);
}
void MusicSearch::search(const QString &music) {
  QString httpUrl = QString("%1/music/%2/music.json").arg(httpUrl_,music);
  qDebug()<<"httpUrl = "<<httpUrl;
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
  emit ToNetTable(musicArray);
}
void MusicSearch::setHttpWeb(QString ip, int port) {
  httpUrl_ =  QString("http://%1:%2").arg(ip,QString::number(port));
}
QString MusicSearch::getHttpWeb() {
  return httpUrl_;
}
















