#include "sessiondata.h"

SessionData::SessionData(std::string name, int dSize, float *data, int cSize, float *coh, QWidget *parent) : Page(name, parent), dataArr(data), cohArr(coh) {

  hrvFrame = new QFrame(parent);
  hrvFrame->setGeometry(45.5, 80, 360, 100);
  hrvFrame->setStyleSheet("border-radius: 5px; border: 1px solid black; background-color: white;");

  hrv = new Hrv(50, hrvFrame);
  hrv->setGeometry(5, 5, 350, 90);

  for(int i = 0; i < dSize; i++){
    hrv->addData(dataArr[i]);
  }

  float low, med, high, sum;
  low = med = high = sum = 0.0;
  for(int i = 0.0; i < cSize; i++){
    if(cohArr[i] == 0) low++;
    if(cohArr[i] == 1) med++;
    if(cohArr[i] == 2) high++;
    sum+=cohArr[i];
  }
  lowButton = new QPushButton(QString::number(low/cSize * 100, 'f', 2) + "%", parent);
  medButton = new QPushButton(QString::number(med/cSize * 100, 'f', 2) + "%", parent);
  highButton = new QPushButton(QString::number(high/cSize * 100, 'f', 2) + "%", parent);

  lowButton->setGeometry(45.5, 10, 360 * low/cSize, 30);
  medButton->setGeometry(45.5 + 360 * low/cSize, 10, 360 * med/cSize, 30);
  highButton->setGeometry(45.5 + 360 * med/cSize + 360 * low/cSize, 10, 360 * high/cSize, 30);

  lowButton->setEnabled(false);
  medButton->setEnabled(false);
  highButton->setEnabled(false);

  lowButton->setStyleSheet("background-color: red; color: black; border: 1px solid black;" );
  medButton->setStyleSheet("background-color: blue; color: black; border: 1px solid black;" );
  highButton->setStyleSheet("background-color: green;color: black; border: 1px solid black;" );

  coherenceLabel = new QLabel("Average Coherence", parent);
  achievementLabel = new QLabel("Achievement Score", parent);
  lengthLabel = new QLabel("Length of Session", parent);
  coherenceVal = new QLabel(QString::number(sum/cSize,'f',2), parent);
  achievementVal = new QLabel(QString::number(sum,'f',2), parent);
  lengthVal = new QLabel(QString::number(dSize/HRV_FRAMES_PER_SECOND,'f',2), parent);

  coherenceLabel->    setGeometry(45.5, 40, 150, 20);
  lengthLabel->       setGeometry(175, 40, 150, 20);
  achievementLabel->  setGeometry(305, 40, 150, 20);
  coherenceVal->      setGeometry(85, 60, 100, 10);
  lengthVal->         setGeometry(210, 60, 100, 10);
  achievementVal->    setGeometry(344, 60, 100, 10);

}

void SessionData::derender(){
  hrvFrame->hide();
  coherenceLabel->hide();
  lengthLabel->hide();
  achievementLabel->hide();
  coherenceVal->hide();
  lengthVal->hide();
  achievementVal->hide();
  lowButton->hide();
  medButton->hide();
  highButton->hide();
}

void SessionData::render(){
  hrvFrame->show();
  coherenceLabel->show();
  lengthLabel->show();
  achievementLabel->show();
  coherenceVal->show();
  lengthVal->show();
  achievementVal->show();
  lowButton->show();
  medButton->show();
  highButton->show();
}

void  SessionData::select(direction dir){
  if(dir == LEFT) hrv->shiftLeft();
  if(dir == RIGHT)hrv->shiftRight();
  hrv->update();
}
