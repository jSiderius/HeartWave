#include "hrv.h"

Hrv::Hrv(float bpm, QWidget *parent) : QWidget(parent), maxVal(150){
  // dataArr.resize(MAX_SESSION_SECONDS*HRV_FRAMES_PER_SECOND);
  // for(int i = 0; i < 100; i++){
  //   dataArr.append(bpm);
  // }
}

void Hrv::addData(float data){
  dataArr[dataSize++]=data;
  // if(dataArr.size() > SECONDS_IN_VIEW*HRV_FRAMES_PER_SECOND){
  //   dataArr.remove(0,dataArr.size()-SECONDS_IN_VIEW*HRV_FRAMES_PER_SECOND);
  // }
  maxVal = qMax(maxVal, data);

  update();
}

void Hrv::paintEvent(QPaintEvent *event){
  int count = dataSize>SECONDS_IN_VIEW*HRV_FRAMES_PER_SECOND ? SECONDS_IN_VIEW*HRV_FRAMES_PER_SECOND : dataSize;
  // qDebug()<<SECONDS_IN_VIEW<<HRV_FRAMES_PER_SECOND<<SECONDS_IN_VIEW*HRV_FRAMES_PER_SECOND;

  QPainter painter(this);
  painter.setRenderHint(QPainter::Antialiasing);
  painter.fillRect(event->rect(), Qt::white);
  painter.setPen(QPen(Qt::black, 2));
  if(count < 2) return;

  double step = (width()-OFFSET_RIGHT)/(count-1.0);
  QPointF *points = new QPointF[count];

  int start = dataSize - count;
  qDebug()<<count;
  for(int i = start; i < start+count; i++){
    points[i-start].setX((i-start) * step);
    // qDebug()<<step<<points[i-start].x();
    points[i-start].setY((1 - (qreal)dataArr[i] / maxVal) * height());
  }
  painter.drawPolyline(points, count);
  painter.translate(width()-OFFSET_RIGHT + 5, (1 - (qreal)dataArr[dataSize-1] / maxVal)*height() - 10);
  painter.drawText(rect(), QString::number(dataArr[dataSize-1], 'f', 2));


  painter.resetTransform();
  painter.drawText(rect(), QString::number(dataSize/HRV_FRAMES_PER_SECOND - SECONDS_IN_VIEW, 'f', 2));

  painter.translate(width()/2 - 20, 0);
  painter.drawText(rect(), QString::number(dataSize/HRV_FRAMES_PER_SECOND - SECONDS_IN_VIEW/2, 'f', 2));

  painter.translate(width()/2 - 40, 0);
  painter.drawText(rect(), QString::number(dataSize/HRV_FRAMES_PER_SECOND, 'f', 2));
  delete[] points;

}

void Hrv::reset(){
  for(int i = 0; i < dataSize; i++){
    dataArr[i]=0;
  }
  update();
}
