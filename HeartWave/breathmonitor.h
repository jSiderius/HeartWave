#ifndef BREATHMONITOR_H
#define BREATHMONITOR_H

#define VECTOR_SIZE 30
#include "defs.h"

class BreathMonitor : public QWidget
{
  Q_OBJECT

  public:
      BreathMonitor(QWidget *parent = nullptr);
      void addData(bool);

  protected:
    void updateRender();
  private:
    QVector<bool> dataArr;
    QVector<QPushButton*> buttons;
};

#endif // BREATHMONITOR_H
