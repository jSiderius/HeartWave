#include "hrv.h"

Hrv::Hrv(float bpm, QWidget *parent) : QWidget(parent), maxVal(150){
  dataArr = new float[static_cast<int>(MAX_SESSION_SECONDS*HRV_FRAMES_PER_SECOND)];
  cohArr = new float[static_cast<int>(MAX_SESSION_SECONDS*HRV_FRAMES_PER_SECOND/5) + 1];
}

void Hrv::addData(float data, int mode){ //probably return coh score if calculated
  dataArr[dataSize++]=data;
  maxVal = qMax(maxVal, data);

  if(dataSize % (static_cast<int>(HRV_FRAMES_PER_SECOND) * COHERENCE_UPDATE_SECS) == 0){ //this is not a good if statement
    float coherence = calculateCoherence(mode);
    cohArr[cohSize++] = coherence;
    achievement += coherence;
  }

  update();
}
void Hrv::addData(float data){ //probably return coh score if calculated
  dataArr[dataSize++]=data;
  maxVal = qMax(maxVal, data);

  if(dataSize % (static_cast<int>(HRV_FRAMES_PER_SECOND) * COHERENCE_UPDATE_SECS) == 0){ //this is not a good if statement
    float coh = calculateCoherence(0);
    cohArr[cohSize++] = coh;
  }

  update();
}

float Hrv::calculateCoherence(int mode){

    if(mode == 1){
        coherence = 16.0;
        achievement+=coherence;
        return 2;
    }else if(mode == 2){
        coherence = 7.0;
        achievement+=coherence;
        return 2;
    }else if(mode == 3){
        coherence = 7.0;
        achievement+=coherence;
        return 2;
    }else if(mode == 4){
        coherence = 4.5;
        achievement+=coherence;
        return 1;
    }else if(mode == 5){
        coherence = 2.5;
        achievement+=coherence;
        return 1;
    }else if(mode == 6){
        coherence = 0.6;
        achievement+=coherence;
        return 0;
    }else if(mode == 7){
        coherence = 0.2;
        achievement+=coherence;
        return 0;
    }else{
        coherence = 16.0;
        achievement+=coherence;
        return 0;
    }
}

void Hrv::paintEvent(QPaintEvent *event){
  int count = dataSize>SECONDS_IN_VIEW*HRV_FRAMES_PER_SECOND ? SECONDS_IN_VIEW*HRV_FRAMES_PER_SECOND : dataSize;

  QPainter painter(this);
  painter.setRenderHint(QPainter::Antialiasing);
  painter.fillRect(event->rect(), Qt::white);
  painter.setPen(QPen(Qt::black, 2));
  if(count < 2) return;

  double step = (width()-OFFSET_RIGHT)/(SECONDS_IN_VIEW*HRV_FRAMES_PER_SECOND);

  QPointF *points = new QPointF[count];

  int start = dataSize - count - offset > 0 ? dataSize - count - offset : 0;
  // qDebug()<<start<<count;
  for(int i = start; i < start+count; i++){
    points[i-start].setX((i-start) * step);
    points[i-start].setY((1 - (qreal)dataArr[i] / maxVal) * height());
  }
  painter.drawPolyline(points, count);
  painter.translate(width()-OFFSET_RIGHT + 5, (1 - (qreal)dataArr[start+count-1] / maxVal)*height() - 10);
  painter.drawText(rect(), QString::number(dataArr[start+count-1], 'f', 2));


  painter.resetTransform();
  painter.drawText(rect(), QString::number(start/HRV_FRAMES_PER_SECOND, 'f', 2));

  painter.translate(width()/2 - 20, 0);
  painter.drawText(rect(), QString::number((start+count/2)/HRV_FRAMES_PER_SECOND, 'f', 2));

  painter.translate(width()/2 - 40, 0);
  painter.drawText(rect(), QString::number((start+count)/HRV_FRAMES_PER_SECOND, 'f', 2));
  delete[] points;

}

void Hrv::reset(float **getDataArr, int &getDataSize, float **getCohArr, int &getCohSize, float &achieve){
  *getDataArr = dataArr;
  *getCohArr = cohArr;
  getDataSize = dataSize;
  getCohSize = cohSize;
  achieve = achievement;

  achievement = 0;
  coherence = 0;
  dataSize = 0;
  offset = 0;
  update();
}

void Hrv::shiftLeft(){
  int count = dataSize>SECONDS_IN_VIEW*HRV_FRAMES_PER_SECOND ? SECONDS_IN_VIEW*HRV_FRAMES_PER_SECOND : dataSize;
  int scroll = static_cast<int>(HRV_FRAMES_PER_SECOND);

  if(offset + scroll + count > dataSize){
    offset = dataSize-count;
  }else{
    offset += scroll;
  }
  qDebug()<<offset;
}

void Hrv::shiftRight(){
  int scroll = static_cast<int>(HRV_FRAMES_PER_SECOND);
  if(offset - scroll < 0){
    offset = 0;
  }else{
    offset -= scroll;
  }
}

float Hrv::getTime(){
  return dataSize/HRV_FRAMES_PER_SECOND;
}

float Hrv::getCoherence(){
  return coherence;
}

float Hrv::getAchievement(){
  return achievement;
}
