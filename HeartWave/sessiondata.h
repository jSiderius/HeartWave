#ifndef SESSIONDATA_H
#define SESSIONDATA_H

#include "defs.h"
#include "page.h"
#include "hrv.h";
#include "breathmonitor.h"

class SessionData : public Page
{
  public:
      SessionData(std::string, int, float*, int, float*, QWidget*);
      Page* click(){  return this; }
      void  derender();
      void  render();
      void  select(direction dir);
      void  update(){}
      void writeToFile();

  private:
      float *dataArr;
      int dataSize;
      float *cohArr;
      int cohSize;

      QFrame *hrvFrame;
      Hrv *hrv;

      QPushButton *lowButton;
      QPushButton *medButton;
      QPushButton *highButton;

      QLabel *coherenceLabel;
      QLabel *lengthLabel;
      QLabel *achievementLabel;
      QLabel *coherenceVal;
      QLabel *lengthVal;
      QLabel *achievementVal;
};

#endif // SESSIONDATA_H
