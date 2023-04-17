#ifndef HRV_H
#define HRV_H

#include "defs.h"

#define OFFSET_RIGHT 45.0
#define SCROLL_SIZE 100
#define DEFAULT_MODE 0

class Hrv : public QWidget
{
  Q_OBJECT

  public:
      Hrv(float = 0, QWidget *parent = nullptr);
      void addData(float, int);
      void addData(float);
      void reset(float **, int &, float **, int &, float &); //ULTIMATELY SHOULD RETURN SESSION DATA
      void shiftLeft();
      void shiftRight();
      float getTime();
      float getCoherence();
      float getAchievement();

  protected:
    void paintEvent(QPaintEvent*);
  private:
    float calculateCoherence(int);

    float *dataArr;
    float *cohArr;
    float coherence = 0;
    float achievement = 0;
    int dataSize = 0;
    int cohSize = 0;

    float maxVal;

    int offset = 0;

};

#endif // HRV_H
