#ifndef HRV_H
#define HRV_H

#include "defs.h"

#define OFFSET_RIGHT 45.0
#define SCROLL_SIZE 100

class Hrv : public QWidget
{
  Q_OBJECT

  public:
      Hrv(float = 0, QWidget *parent = nullptr);
      void addData(float);
      void reset(float **, int &, float **, int &); //ULTIMATELY SHOULD RETURN SESSION DATA
      void shiftLeft();
      void shiftRight();
      float getTime();
      float getCoherence();
      float getAchievement();

  protected:
    void paintEvent(QPaintEvent*);
  private:
    float calculateCoherence();

    float *dataArr;
    float *cohArr;
    int dataSize = 0;
    int cohSize = 0;

    float maxVal;

    int offset = 0;
};

#endif // HRV_H
