#include "MusicHttp.h"
#include <QFile>
#include <QDebug>
#include <QString>
#include <QDir>
#include <utility>

MusicHttp::MusicHttp(const QString &filename, QObject *parent):
    QObject(parent),
    state_(MusicHttpState::MusicHttpSuccessState),
    filename_(std::move(filename))
{
  manager_ = new QNetworkAccessManager(this);
}

MusicHttp::~MusicHttp() {
  delete manager_;
}

void MusicHttp::get(const QString &httpUrl) {
  if (QFile(filename_).exists()){
    QFile::remove(filename_);
  }
  state_ = MusicHttpState::MusicHttpSuccessState;
  QUrl url(httpUrl);
  QNetworkRequest req(url);
  QNetworkReply *reply = manager_->get(req);
  connect(reply,&QNetworkReply::readyRead, this,&MusicHttp::readData);  // 只要有数据来就会触发
  connect(reply,&QNetworkReply::finished, this,&MusicHttp::handleFinished); // 全部数据下载完
  connect(reply,&QNetworkReply::errorOccurred, this,&MusicHttp::handleError);
}
void MusicHttp::readData() {
  // 在信号与槽机制中，当一个信号被发射时，Qt 将会调用相应的槽函数
  // 并且在槽函数内部可以使用 sender() 方法来获取发射该信号的对象
  auto *reply = qobject_cast<QNetworkReply *>(sender());

  QByteArray data = reply->readAll();

  QFile file(filename_);
  if (!file.open(QFile::Append | QFile::WriteOnly)){
    qDebug()<<"打开文件失败"<<filename_;
    return;
  }
  if (!file.write(data)){
    qDebug()<<"写入文件失败"<<filename_;
    return;
  }
  file.close();

  reply->deleteLater();
}
void MusicHttp::handleError(QNetworkReply::NetworkError code) {
  qDebug()<<"NetWorkError code : "<<code;
  state_ = MusicHttpState::MusicHttpErrorState;
}
bool MusicHttp::isError() {
  return state_ == MusicHttpState::MusicHttpErrorState;
}
QByteArray MusicHttp::readAll() {

  QFile file(filename_);

  if (!file.open(QFile::ReadOnly)){
    qDebug()<<"打开文件失败"<<filename_;
    return {};
  }
  QByteArray data = file.readAll();
  file.close();
  return data;
}
void MusicHttp::handleFinished() {
  auto *reply = qobject_cast<QNetworkReply *>(sender());
  if (reply->error() == QNetworkReply::NoError){
    emit finishedRead();
  }
  reply->deleteLater();
}


