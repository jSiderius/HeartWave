#include "hrv.h"

Hrv::Hrv(float bpm, QWidget *parent) : QWidget(parent), maxVal(150){
  dataArr = new float[static_cast<int>(MAX_SESSION_SECONDS*HRV_FRAMES_PER_SECOND)];
  cohArr = new float[static_cast<int>(MAX_SESSION_SECONDS*HRV_FRAMES_PER_SECOND/5) + 1];
}

void Hrv::addData(float data){ //probably return coh score if calculated
  dataArr[dataSize++]=data;
  maxVal = qMax(maxVal, data);

  if(dataSize % (static_cast<int>(HRV_FRAMES_PER_SECOND)) == 0){ //this is not a good if statement
    cohArr[cohSize++] = rand()%3;
  }

  update();
}

void Hrv::paintEvent(QPaintEvent *event){
  int count = dataSize>SECONDS_IN_VIEW*HRV_FRAMES_PER_SECOND ? SECONDS_IN_VIEW*HRV_FRAMES_PER_SECOND : dataSize;

  QPainter painter(this);
  painter.setRenderHint(QPainter::Antialiasing);
  painter.fillRect(event->rect(), Qt::white);
  painter.setPen(QPen(Qt::black, 2));
  if(count < 2) return;

  double step = (width()-OFFSET_RIGHT)/(count-1.0);
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

void Hrv::reset(float **getDataArr, int &getDataSize, float **getCohArr, int &getCohSize){
  *getDataArr = dataArr;
  *getCohArr = cohArr;
  getDataSize = dataSize;
  getCohSize = cohSize;

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
