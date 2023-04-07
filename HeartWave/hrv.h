#ifndef HRV_H
#define HRV_H

#include "defs.h"

class Hrv : public QWidget
{
  Q_OBJECT

  public:
      Hrv(int = 0, QWidget *parent = nullptr);
      void addData(int);

  protected:
    void paintEvent(QPaintEvent*);
  private:
    QVector<int> dataArr;
    int maxVal;
};

#endif // HRV_H
