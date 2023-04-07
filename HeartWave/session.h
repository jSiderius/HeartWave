#ifndef SESSION_H
#define SESSION_H

#include "defs.h"
#include "page.h"
#include "hrv.h";

#define BATTERY_HEIGHT 30.0
#define HEART_BEAT_TIME 20000000

class Session : public Page
{
  public:
      Session(std::string, QWidget*);
      Page* click();
      void  derender();
      void  render();
      void  select(direction dir);
      void  update();

      float batteryPercent = 25;

      float achievementVal = 11;
      float lengthVal = 11;
      float coherenceVal = 6;

  private:
    void initGUI(QWidget*);

    QPushButton *batteryEmpty;
    QPushButton *batteryFull;
    QPushButton *coherenceIndicator;

    QLabel *coherence;
    QLabel *length;
    QLabel *achievement;
    QLabel *coherenceValWidget;
    QLabel *lengthValWidget;
    QLabel *achievementValWidget;
    QPushButton *heartBeat;
    QFrame *hrvFrame;
    Hrv *hrv;
    QFrame *breathFrame;

    int bpm = 60;
    struct timeval heartBeatTimestamp;
    struct timeval bpmUpdateTimestamp;


};

#endif // SESSION_H
