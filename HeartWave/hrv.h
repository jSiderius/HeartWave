#ifndef HRV_H
#define HRV_H

#include "defs.h"

class Hrv : public QWidget
{
  Q_OBJECT

  public:
      Hrv(int = 0, QWidget *parent = nullptr);
      void addData(int);
      void reset(); //ULTIMATELY SHOULD RETURN SESSION DATA 

  protected:
    void paintEvent(QPaintEvent*);
  private:
    QVector<int> dataArr;
    int maxVal;
};

#endif // HRV_H
