//
// Created by xy on 2024-07-10.
//

// You may need to build the project (run Qt uic code generator) to get "ui_MusicWindow.h" resolved

#include "musicwindow.h"
#include "ui_MusicWindow.h"
#include <QTime>
#include <QAudioOutput>

MusicWindow::MusicWindow(QWidget *parent) :
    QWidget(parent), ui(new Ui::MusicWindow) {
  ui->setupUi(this);
  musicSearch_ = new MusicSearch(this);
  musicPlayer_ = new QMediaPlayer(this);
  audioOutput_ = new QAudioOutput(this);
  musicPlayer_->setAudioOutput(audioOutput_);

  initQTableWidget();

  connect(ui->searchlineEdit, &QLineEdit::returnPressed, this, &MusicWindow::searchMusic);
  connect(musicSearch_, &MusicSearch::ToNetTable, this, &MusicWindow::showNetToTable);
  connect(ui->netTableWidget, &QTableWidget::cellDoubleClicked, this, &MusicWindow::playNetMusic);
  connect(musicPlayer_,&QMediaPlayer::durationChanged, this,&MusicWindow::updateDurationChanged);
  connect(musicPlayer_,&QMediaPlayer::positionChanged, this,&MusicWindow::updatePositionChanged);
  connect(ui->playSlider,&QSlider::sliderMoved,this,&MusicWindow::updateSliderMoved);
}

MusicWindow::~MusicWindow() {
  delete ui;
}
void MusicWindow::searchMusic() {
  QString musicName = ui->searchlineEdit->text();
  musicSearch_->search(musicName);
}
void MusicWindow::initQTableWidget() {
  // 隐藏前三列
  ui->netTableWidget->setColumnHidden(0, true);
  ui->netTableWidget->setColumnHidden(1, true);
  ui->netTableWidget->setColumnHidden(2, true);

  ui->localTableWidget->setColumnHidden(0, true);
  ui->localTableWidget->setColumnHidden(1, true);
  ui->localTableWidget->setColumnHidden(2, true);


  // 设置表头自适应宽度
  ui->netTableWidget->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
  ui->localTableWidget->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);

  // 设置表格不可编辑
  ui->netTableWidget->setEditTriggers(QAbstractItemView::NoEditTriggers);
  ui->localTableWidget->setEditTriggers(QAbstractItemView::NoEditTriggers);

  // 隐藏行号
  ui->netTableWidget->verticalHeader()->setVisible(false);
  ui->localTableWidget->verticalHeader()->setVisible(false);

  // 设置选择行为为选择行
  ui->netTableWidget->setSelectionBehavior(QAbstractItemView::SelectRows);
  ui->localTableWidget->setSelectionBehavior(QAbstractItemView::SelectRows);

  // 清除焦点
  ui->netTableWidget->clearFocus();
  ui->localTableWidget->clearFocus();
}
void MusicWindow::showNetToTable(QJsonArray data) {
  ui->netTableWidget->setRowCount(data.size());

  for (int i = 0; i < data.size(); i++) {
    QString httpWeb = musicSearch_->getHttpWeb();
    if (httpWeb == nullptr) return;
    QJsonObject object = data[i].toObject();
    QString musicName = object["musicName"].toString();
    QString albumName = object["albumName"].toString();
    qint32 MusicDuration = object["duration"].toInt();
    QString musciPath = object["path"].toString();
    httpWeb = httpWeb.append(musciPath);
    QString musicMp3 = httpWeb.append(object["mp3"].toString());
    QString MusicLrc = object["lrc"].toString();
    QString MusicImg = object["img"].toString();

    QTime time = QTime::fromMSecsSinceStartOfDay(MusicDuration * 1000);

    // 设置每行的数据
    ui->netTableWidget->setItem(i, 0, new QTableWidgetItem(musicMp3));
    ui->netTableWidget->setItem(i, 1, new QTableWidgetItem(MusicLrc));
    ui->netTableWidget->setItem(i, 2, new QTableWidgetItem(MusicImg));
    ui->netTableWidget->setItem(i, 3, new QTableWidgetItem(musicName));
    ui->netTableWidget->setItem(i, 4, new QTableWidgetItem(albumName));
    ui->netTableWidget->setItem(i, 5, new QTableWidgetItem(time.toString("mm:ss")));
  }

}
void MusicWindow::playNetMusic(int row, int column) {
  QString mp3Url = ui->netTableWidget->item(row, 0)->text();
  QString lrcUrl = ui->netTableWidget->item(row, 1)->text();
  QString imgUrl = ui->netTableWidget->item(row, 2)->text();

  QStringList list;
  list << mp3Url << lrcUrl << imgUrl;
  playMusic(list);

  return;
}
void MusicWindow::playMusic(const QStringList &urlList) {
  QString mp3Url = urlList[0];
  QString lrcUrl = urlList[1];
  QString imgUrl = urlList[2];

  qDebug()<<"mp3Url = "<<mp3Url;
  QUrl url(mp3Url);
  musicPlayer_->setSource(url); // 播放源
  audioOutput_->setVolume(50);  // 音量
  musicPlayer_->play(); // 播放

}
void MusicWindow::updateDurationChanged(qint64 duration) {
  QTime time = QTime::fromMSecsSinceStartOfDay(duration);
  ui->endlabel->setText(time.toString("mm:ss"));

  ui->playSlider->setRange(0,duration);
}
void MusicWindow::updatePositionChanged(qint64 position) {
  ui->playSlider->setValue(position);
  QTime time = QTime::fromMSecsSinceStartOfDay(position);
  ui->startlabel->setText(time.toString("mm:ss"));

}
void MusicWindow::updateSliderMoved(int position) {
  musicPlayer_->setPosition(position);
}
