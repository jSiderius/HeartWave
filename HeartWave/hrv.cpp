#include "hrv.h"

Hrv::Hrv(int bpm, QWidget *parent) : QWidget(parent), maxVal(150){
  for(int i = 0; i < 100; i++){
    dataArr.append(bpm);
  }
}

void Hrv::addData(int data){
  dataArr.append(data);
  if(dataArr.size() > 100){
    dataArr.remove(0,dataArr.size()-100);
  }
  maxVal = qMax(maxVal, data);

  update();
}

void Hrv::paintEvent(QPaintEvent *event){
  int count = dataArr.count();

  QPainter painter(this);
  painter.setRenderHint(QPainter::Antialiasing);
  painter.fillRect(event->rect(), Qt::white);
  painter.setPen(QPen(Qt::black, 2));
  if(count < 2) return;

  int step = width()/(count-1);
  QPointF *points = new QPointF[count];

  for(int i = 0; i < count; i++){
    points[i].setX(i * step);
    points[i].setY((1 - (qreal)dataArr[i] / maxVal) * height());
  }
  
  painter.drawPolyline(points, count);
  delete[] points;
}