#include "hrv.h"

Hrv::Hrv(int bpm, QWidget *parent) : QWidget(parent), maxVal(150){
  for(int i = 0; i < 100; i++){
    dataArr.append(bpm);
  }
}

void Hrv::addData(int data){
  dataArr.append(data);
  if(dataArr.size() > 80){
    dataArr.remove(0,dataArr.size()-80);
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

  painter.translate(width()-20, (1 - (qreal)dataArr[count-1] / maxVal)*height() - 10);
  painter.drawText(rect(), QString::number(dataArr[count-1]));

  delete[] points;
}

void Hrv::reset(){
  int count = dataArr.count();
  for(int i = 0; i < count; i++){
    dataArr[i]=0;
  }
  update();
}
