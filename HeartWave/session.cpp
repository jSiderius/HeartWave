#include "session.h"

Session::Session(std::string n, QWidget* parent) : Page(n, parent)
{
  gettimeofday(&heartBeatTimestamp, NULL);
  initGUI(parent);
}

void Session::initGUI(QWidget *parent){
  batteryEmpty = new QPushButton(parent);
  batteryFull = new QPushButton(parent);
  qDebug()<<"1";
  //size = 10
  float endA = BATTERY_HEIGHT * (100.0 - batteryPercent) / 100.0;
  batteryEmpty->setGeometry(10, 10, 20, endA);
  batteryFull->setGeometry(10, 10.0+endA,20, BATTERY_HEIGHT * batteryPercent / 100.0);

  batteryEmpty->setStyleSheet("background-color: white; border: 1px solid black; border-bottom-left-radius: 0px; border-bottom-right-radius: 0px; border-top-left-radius: 2px; border-top-right-radius: 2px;");
  batteryFull->setStyleSheet("background-color: green; border: 1px solid black; border-top-left-radius: 0px; border-top-right-radius: 0px; border-bottom-left-radius: 2px; border-bottom-right-radius: 2px;");
  qDebug()<<"2";
  coherence = new QLabel("Coherence", parent);
  length = new QLabel("Length", parent);
  achievement = new QLabel("Achievement", parent);
  coherenceValWidget = new QLabel(QString::number(coherenceVal,'f',1), parent);
  lengthValWidget = new QLabel(QString::number(lengthVal,'f',2), parent);
  achievementValWidget = new QLabel(QString::number(achievementVal,'f',1), parent);
  qDebug()<<"3";
  coherence->           setGeometry(65, 10, 100, 20);
  length->              setGeometry(200, 10, 100, 20);
  achievement->         setGeometry(300, 10, 100, 20);
  coherenceValWidget->  setGeometry(80, 30, 100, 10);
  lengthValWidget->     setGeometry(205, 30, 100, 10);
  achievementValWidget->setGeometry(322, 30, 100, 10);

  heartBeat = new QPushButton(parent);
  heartBeat->setGeometry(411, 10, 30, 30);
  heartBeat->setStyleSheet("QPushButton { border-radius: 15px; background-color: red; }");

  hrvFrame = new QFrame(parent);
  hrvFrame->setGeometry(45.5, 50, 360, 100);
  hrvFrame->setStyleSheet("border-radius: 5px; border: 1px solid black; background-color: white;");
  qDebug()<<"4";
  breathFrame = new QFrame(parent);
  breathFrame->setGeometry(45.5, 160, 360, 25);
  breathFrame->setStyleSheet("border-radius: 5px; border: 1px solid black; background-color: white;");
}

void Session::update(){
  // qDebug()<<abs(difftime(heartBeatTimestamp, time(NULL)))<<" "<<1/bpm;
  struct timeval now;
  gettimeofday(&now, NULL);
  // long seconds - (now.tv_sec - heartBeatTimestamp.tv_sec) * 1000000
  long microseconds = (now.tv_sec * 1000000 + now.tv_usec) - (heartBeatTimestamp.tv_sec * 1000000 + heartBeatTimestamp.tv_usec);//

  qDebug()<<microseconds<<1000000/(bpm*60);
  if(microseconds > (60*1000000/(bpm))){
      gettimeofday(&heartBeatTimestamp, NULL);
      heartBeat->setStyleSheet("QPushButton { border-radius: 15px; background-color: red; }");
  }else if(microseconds < HEART_BEAT_TIME/bpm){

  }else{
      heartBeat->setStyleSheet("QPushButton { border-radius: 15px; background-color: blue; }");
  }
}

Page* Session::click(){
  return this;
}

void  Session::derender(){
  batteryEmpty->hide();
  batteryFull->hide();
  coherence->hide();
  length->hide();
  achievement->hide();
  coherenceValWidget->hide();
  lengthValWidget->hide();
  achievementValWidget->hide();
  heartBeat->hide();
  hrvFrame->hide();
  breathFrame->hide();
}

void  Session::render(){
  batteryEmpty->show();
  batteryFull->show();
  coherence->show();
  length->show();
  achievement->show();
  coherenceValWidget->show();
  lengthValWidget->show();
  achievementValWidget->show();
  heartBeat->show();
  hrvFrame->show();
  breathFrame->show();
}

void  Session::select(direction dir){

}
