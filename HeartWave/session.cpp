#include "session.h"

Session::Session(std::string n, QWidget* parent) : Page(n, parent){
  gettimeofday(&heartBeatTimestamp, NULL);
  initGUI(parent);
}

void Session::initGUI(QWidget *parent){
  batteryEmpty = new QPushButton(parent);
  batteryFull = new QPushButton(parent);

  float endA = BATTERY_HEIGHT * (100.0 - batteryPercent) / 100.0;
  batteryEmpty->setGeometry(10, 40, 20, endA);
  batteryFull->setGeometry(10, 40.0+endA,20, BATTERY_HEIGHT * batteryPercent / 100.0);

  batteryEmpty->setStyleSheet("background-color: white; border: 1px solid black; border-bottom-left-radius: 0px; border-bottom-right-radius: 0px; border-top-left-radius: 2px; border-top-right-radius: 2px;");
  batteryFull->setStyleSheet("background-color: green; border: 1px solid black; border-top-left-radius: 0px; border-top-right-radius: 0px; border-bottom-left-radius: 2px; border-bottom-right-radius: 2px;");

  coherence = new QLabel("Coherence", parent);
  length = new QLabel("Length", parent);
  achievement = new QLabel("Achievement", parent);
  coherenceValWidget = new QLabel(QString::number(coherenceVal,'f',1), parent);
  lengthValWidget = new QLabel(QString::number(lengthVal,'f',2), parent);
  achievementValWidget = new QLabel(QString::number(achievementVal,'f',1), parent);

  coherence->           setGeometry(65, 40, 100, 20);
  length->              setGeometry(200, 40, 100, 20);
  achievement->         setGeometry(300, 40, 100, 20);
  coherenceValWidget->  setGeometry(80, 60, 100, 10);
  lengthValWidget->     setGeometry(205, 60, 100, 10);
  achievementValWidget->setGeometry(322, 60, 100, 10);

  coherenceIndicator = new QPushButton(parent);
  coherenceIndicator->setGeometry(10, 10, 431, 20);


  heartBeat = new QPushButton(parent);
  heartBeat->setGeometry(411, 40, 30, 30);
  heartBeat->setStyleSheet("QPushButton { border-radius: 15px; background-color: red; }");

  hrvFrame = new QFrame(parent);
  hrvFrame->setGeometry(45.5, 80, 360, 100);
  hrvFrame->setStyleSheet("border-radius: 5px; border: 1px solid black; background-color: white;");

  hrv = new Hrv(bpm, hrvFrame);
  hrv->setGeometry(5, 5, 350, 90);

  breathFrame = new QFrame(parent);
  breathFrame->setGeometry(45.5, 190, 360, 25);
  breathFrame->setStyleSheet("border-radius: 5px; border: 1px solid black; background-color: white;");
}

void Session::update(){
  // UPDATE HEART BEAT
  struct timeval now;
  gettimeofday(&now, NULL);
  long microseconds = (now.tv_sec * 1000000 + now.tv_usec) - (heartBeatTimestamp.tv_sec * 1000000 + heartBeatTimestamp.tv_usec);//
  if(microseconds > (60*1000000/(bpm))){
      coherenceVal++;
      gettimeofday(&heartBeatTimestamp, NULL);
      heartBeat->setStyleSheet("QPushButton { border-radius: 15px; background-color: red; }");
  }else if(microseconds < HEART_BEAT_TIME/bpm){

  }else{
      heartBeat->setStyleSheet("QPushButton { border-radius: 15px; background-color: blue; }");
  }

  //UPDATE COHERENCE INDICATOR
  if(coherenceVal < 10){
    coherenceIndicator->setStyleSheet("background-color: red");
  }else if(coherenceVal < 20){
    coherenceIndicator->setStyleSheet("background-color: blue");
  }else{
    coherenceIndicator->setStyleSheet("background-color: green");
  }

  //UPDATE HRV GRAPH
  microseconds = (now.tv_sec * 1000000 + now.tv_usec) - (bpmUpdateTimestamp.tv_sec * 1000000 + bpmUpdateTimestamp.tv_usec);
  if(abs(microseconds) > (1000000/8)){
    gettimeofday(&bpmUpdateTimestamp, NULL);
    int rand = std::rand()%21 - 10;
    bpm = bpm + rand;
    hrv->addData(bpm);
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
  coherenceIndicator->hide();
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