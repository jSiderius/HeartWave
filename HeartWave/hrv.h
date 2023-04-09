#ifndef HRV_H
#define HRV_H

#include "defs.h"

#define SECONDS_IN_VIEW 4.0 
#define OFFSET_RIGHT 45.0

class Hrv : public QWidget
{
  Q_OBJECT

  public:
      Hrv(float = 0, QWidget *parent = nullptr);
      void addData(float);
      void reset(); //ULTIMATELY SHOULD RETURN SESSION DATA

  protected:
    void paintEvent(QPaintEvent*);
  private:
    float dataArr[static_cast<int>(MAX_SESSION_SECONDS*HRV_FRAMES_PER_SECOND)];
    int dataSize = 0;
    float maxVal;
};

#endif // HRV_H
