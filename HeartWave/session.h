#ifndef SESSION_H
#define SESSION_H

#include "defs.h"
#include "page.h"
#include "hrv.h";
#include "breathmonitor.h"

#define BATTERY_HEIGHT 30.0
#define HEART_BEAT_TIME 20000000
#define BREATHING_RATE 3

class Session : public Page
{
  public:
      Session(std::string, QWidget*);
      Page* click();
      void  derender();
      void  render();
      void  select(direction dir);
      void  update();

      void stopSession();
      void startSession();

      void updateHeartBeat();
      void updateCoherence();
      void updateHrvGraph();
      void updateBreathMonitor();
      void updateText();

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
    BreathMonitor *breathMonitor;

    int bpm = 60;
    struct timeval heartBeatTimestamp;
    struct timeval bpmUpdateTimestamp;
    struct timeval breathTimestamp;
    struct timeval breathTick;
    struct timeval startTimestamp;

    bool sessionRunning;


};

#endif // SESSION_H
