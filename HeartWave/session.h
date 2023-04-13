#ifndef SESSION_H
#define SESSION_H

#include "defs.h"
#include "page.h"
#include "menu.h"
#include "hrv.h";
#include "breathmonitor.h"
#include "sessiondata.h"

#define BATTERY_HEIGHT 30.0
#define HEART_BEAT_TIME 20000000
#define SIN_STEP_PER_SECOND 1.63369 //bounds for coherence (.251327, 1.63369)

class Session : public QObject, public Page
{
  Q_OBJECT
  public:
      Session(std::string, Menu*, int&, QWidget*);
      ~Session(){}
      Page* click();
      void  derender();
      void  render();
      void  select(direction dir){}
      void  update();

      void stopSession();
      void startSession();

      void updateHeartBeat();
      void updateCoherence();
      // void updateHrvGraph();
      void updateBreathMonitor();
      void updateText();

  private:
    QWidget *parent;
    Menu *sessionDataMenu;
    int &breathingRate;

    float achievementVal = 11;
    float lengthVal = 11;
    float coherenceVal = 6;

    void initGUI(QWidget*);
    void coherenceChangeAudio();

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

    float bpm = 60;
    float sinCurr = 0;
    int hrvUpdateTicks = 0;
    struct timeval heartBeatTimestamp;
    struct timeval bpmUpdateTimestamp;
    struct timeval breathTimestamp;
    struct timeval startTimestamp;

    int breathTick = 0;
    int secondTick = 0;

    bool sessionRunning;
    bool sensorConnected = false;
    int numSessions = 0;

    private slots:
      void updateHrvGraph();
      void changeConnection();


};

#endif // SESSION_H
