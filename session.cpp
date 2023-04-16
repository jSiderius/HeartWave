#include "session.h"

Session::Session(std::string n, Menu *m, int &br, QWidget* parent, int &type, int &chall) : Page(n, parent), sessionDataMenu(m), sessionRunning(false), breathingRate(br), parent(parent), mode(type), challLevel(chall) {
    //qDebug()<<"Chall"<<challLevel;
    initGUI(parent);
}

void Session::initGUI(QWidget *parent){

  coherence = new QLabel("Coherence", parent);
  length = new QLabel("Length", parent);
  achievement = new QLabel("Achievement", parent);
  coherenceValWidget = new QLabel(QString::number(coherenceVal,'f',1), parent);
  lengthValWidget = new QLabel(QString::number(lengthVal,'f',2), parent);
  achievementValWidget = new QLabel(QString::number(achievementVal,'f',1), parent);
  coherenceChange = new QLabel("Coherence Value Has Changed!", parent);
  cohChange = new QTimer(parent);
  connect(cohChange, &QTimer::timeout, parent, [=] () -> void {coherenceChange->setVisible(false);});

  coherence->           setGeometry(65, 40, 100, 20);
  length->              setGeometry(200, 40, 100, 20);
  achievement->         setGeometry(300, 40, 100, 20);
  coherenceValWidget->  setGeometry(80, 60, 100, 10);
  lengthValWidget->     setGeometry(205, 60, 100, 10);
  achievementValWidget->setGeometry(322, 60, 100, 10);
  coherenceChange->setGeometry(140, 0, 200, 20);
  coherenceChange->setVisible(false);

  coherenceIndicator = new QPushButton(parent);
  coherenceIndicator->setGeometry(10, 19, 431, 20);


  heartBeat = new QPushButton(parent);
  heartBeat->setGeometry(411, 40, 30, 30);
  heartBeat->setStyleSheet("QPushButton { border-radius: 15px; background-color: red; }");
  connect(heartBeat, &QPushButton::pressed, this, &Session::changeConnection);

  hrvFrame = new QFrame(parent);
  hrvFrame->setGeometry(45.5, 80, 360, 100);
  hrvFrame->setStyleSheet("border-radius: 5px; border: 1px solid black; background-color: white;");

  hrv = new Hrv(bpm, hrvFrame);
  hrv->setGeometry(5, 5, 350, 90);

  breathFrame = new QFrame(parent);
  breathFrame->setGeometry(45.5, 190, 360, 25);
  breathFrame->setStyleSheet("border-radius: 5px; border: 1px solid black; background-color: white;");

  breathMonitor = new BreathMonitor(breathFrame);
  breathMonitor->setGeometry(5,5,350,15);
}

void Session::update(){
    updateHeartBeat();
    updateCoherence();
    updateHrvGraph();
    updateBreathMonitor();
    updateText();
}

void Session::updateHeartBeat(){
  struct timeval now;
  gettimeofday(&now, NULL);
  long microseconds = (now.tv_sec * 1000000 + now.tv_usec) - (heartBeatTimestamp.tv_sec * 1000000 + heartBeatTimestamp.tv_usec);//
  if(!sensorConnected){
    heartBeat->setStyleSheet("QPushButton { border-radius: 15px; background-color: blue; }");
  }else if(!sessionRunning){
    heartBeat->setStyleSheet("QPushButton { border-radius: 15px; background-color: (238,238,238); }");
  }else if(microseconds > (60*1000000/(bpm))){
      gettimeofday(&heartBeatTimestamp, NULL);
      heartBeat->setStyleSheet("QPushButton { border-radius: 15px; background-color: red; }");
  }else if(microseconds < HEART_BEAT_TIME/bpm){

  }else{
      heartBeat->setStyleSheet("QPushButton { border-radius: 15px; background-color: (238,238,238); }");
  }
}

void Session::updateCoherence(){
    float min = 0.5;
    float max = 0.9;
    if(challLevel == 1){
        min = 0.5;
        max = 0.9;
    }else if(challLevel == 2){
        min = 0.6;
        max = 2.1;
    }else if(challLevel == 3){
        min = 1.8;
        max = 4.0;
    }else if(challLevel == 4){
        min = 4.0;
        max = 6.0;
    }
    if(!sessionRunning){
        coherenceIndicator->setStyleSheet("background-color: grey");
    }else if(coherenceVal < min){
        coherenceIndicator->setStyleSheet("background-color: red");
    }else if(coherenceVal < max){
        coherenceIndicator->setStyleSheet("background-color: blue");
    }else{
        coherenceIndicator->setStyleSheet("background-color: green");
    }
}

void Session::updateHrvGraph(){
  if(!sessionRunning)return;
  struct timeval now;
  gettimeofday(&now, NULL);
  long microseconds = (now.tv_sec * 1000000 + now.tv_usec) - (startTimestamp.tv_sec * 1000000 + startTimestamp.tv_usec);
  if(abs(microseconds) > hrvUpdateTicks*1000000/HRV_FRAMES_PER_SECOND){
    gettimeofday(&bpmUpdateTimestamp, NULL);
    hrvUpdateTicks++;
    sinCurr += SIN_STEP_PER_SECOND/HRV_FRAMES_PER_SECOND;
    bpm = getBPM(sinCurr);
    hrv->addData(bpm, mode);
  }
}

void Session::updateBreathMonitor(){

  if(!sessionRunning)return;
  if(hrv->getTime() > breathingRate * breathTick){
    breathTick++;
    secondTick++;
    breathMonitor->addData(true);
  }else if(hrv->getTime() > secondTick){
    secondTick++;
    breathMonitor->addData(false);
  }
}

void Session::updateText(){
  coherenceVal = hrv->getCoherence();
  coherenceChangeAlert();
  achievementVal = hrv->getAchievement();
  lengthValWidget->setText(QString::number(hrv->getTime(), 'f', 2));
  coherenceValWidget->setText(QString::number(coherenceVal,'f',1));
  achievementValWidget->setText(QString::number(achievementVal,'f',1));
}

void Session::stopSession(){
  if(!sessionRunning) return;
  sessionRunning = false;
  breathTick = 0;
  secondTick = 0;
  lengthValWidget->setText("0:0.00");
  heartBeat->setStyleSheet("border-radius: 15px; background-color: (238,238,238);");

  float *dataArr;
  float *cohArr;
  int dataSize, cohSize;
  hrv->reset(&dataArr, dataSize, &cohArr, cohSize);
  SessionData *sd = new SessionData("Current Session Data"+std::to_string(++numSessions), dataSize, dataArr, cohSize, cohArr, parent);
  hrvUpdateTicks = 0;
  sessionDataMenu->add(sd);
  breathMonitor->reset();
}

void Session::startSession(){
  if(sessionRunning || !sensorConnected)  return;
  sessionRunning = true;
  gettimeofday(&heartBeatTimestamp, NULL);
  gettimeofday(&breathTimestamp, NULL);
  gettimeofday(&bpmUpdateTimestamp, NULL);
  gettimeofday(&startTimestamp, NULL);
}

Page* Session::click(){
  sessionRunning ? stopSession() : startSession();
  return this;
}

void  Session::derender(){
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
  coherence->show();
  length->show();
  achievement->show();
  coherenceValWidget->show();
  lengthValWidget->show();
  achievementValWidget->show();
  heartBeat->show();
  hrvFrame->show();
  breathFrame->show();
  coherenceIndicator->show();
}

void Session::changeConnection(){
  sensorConnected = !sensorConnected;
  if(!sensorConnected && sessionRunning) stopSession();
}

void Session::coherenceChangeAlert(){
    if(coherenceVal == prevCoherence){
        return;
    }
    coherenceChange->setVisible(true);
    cohChange->start(5000);
    prevCoherence = coherenceVal;
}

float Session::getBPM(float in){
    changed = (changed + 1)%5;
    if(changed > 0){return std::sin(in)*x + y;}
    int random = rand()%10;
    int randPosNeg= rand()%2;
    int n = 1;
    if(randPosNeg == 1){
        n = -1;
    }
    if(mode == 1){//mid vals, high coh
        x = 15;
        y = 70;
    }else if(mode == 2){//extreme vals, high coh
        x = 25;
        y = 70;
    }else if(mode == 3){//low vals, high coh
        x = 10;
        y = 70;
    }else if(mode == 4){ //semi-random, mid coh
        if(random == 10 && x < 20){
            x++;
        }else if(random == 9 && x > 10){
            x--;
        }else if(random == 8 && y < 90){
            y++;
        }else if(random == 7 && y > 50){
            y--;
        }
    }else if(mode == 5){ //semi-random, mid-low coh
        if(random == 10 && x < 20){
            x += 2;
        }else if(random == 9 && x > 12){
            x -=2;
        }else if(random == 8 && y < 90){
            y +=2;
        }else if(random == 7 && y > 50){
            y -=2;
        }else if(random == 6 && x < 25 && y < 100){
            x++;
            y++;
        }else if(random == 5 && x > 8 && y > 40){
            x--;
            y--;
        }
    }else if(mode == 6){ //random, low coh
        if(random == 10 && x < 20){
            x += 2;
        }else if(random == 9 && x > 12){
            x -=2;
        }else if(random == 8 && y < 90){
            y +=2;
        }else if(random == 7 && y > 50){
            y -=2;
        }else if(random == 6 && x < 25 && y < 100){
            x++;
            y++;
        }else if(random == 5 && x > 10 && y > 40){
            x--;
            y--;
        }else if(random == 1 && x > 10 && x < 25){
            x += n*5;
        }
    }else if(mode == 7){ //very random, low coh
        if(random == 10){
            x = 25;
            y = 90;
        }else if(random == 9){
            x = 15;
            y = 50;
        }else if(random == 8 && y < 90 && x < 25){
            y +=2;
            x +=2;
        }else if(random == 7 && y > 50 && x > 10){
            y -=2;
            x -=2;
        }else if(random == 6 && x < 25 && y < 100){
            x++;
            y++;
        }else if(random == 5 && x > 10 && y > 40){
            x--;
            y--;
        }else if(random > 2 && x > 10 && x < 25){
            x += n*5;
        }else if(y > 30 && y < 110){
            y += n*5;
        }
    }else{
        x = 10;
        y = 70;
    }
    return std::sin(in)*x + y;
}
