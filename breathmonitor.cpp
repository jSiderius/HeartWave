#include "breathmonitor.h"

// breathMonitor->setGeometry(5,5,350,15);
BreathMonitor::BreathMonitor(QWidget *parent)
{
  for(int i = 0; i < VECTOR_SIZE; i++){
    QPushButton *button = new QPushButton(parent);
    button->setStyleSheet("background-color: grey");
    button->setGeometry(5 + i * 350/(VECTOR_SIZE-2),5,350/(VECTOR_SIZE-2), 15);
    button->hide();
    buttons.append(button);
    dataArr.append(false);
  }

}

void BreathMonitor::addData(bool data){
  for(int i = 0; i < 3; i++){
    dataArr.append(data);
    if(dataArr.size() > VECTOR_SIZE){
      dataArr.remove(0,dataArr.size()-VECTOR_SIZE);
    }
    if(!data)continue;
  }
  updateRender();
}

void BreathMonitor::updateRender(){
  int count = dataArr.count();
  for(int i = 0; i < count-2; i++){
    if(dataArr[i]){
      buttons[i]->show();
    }else{
      buttons[i]->hide();
    }
  }
}

void BreathMonitor::reset(){
  int count = dataArr.count();
  for(int i = 0; i < count; i++){
    dataArr[i]=false;
  }
  updateRender();
}
