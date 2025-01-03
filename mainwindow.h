#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "defs.h"
#include "menu.h"
#include "session.h"
#include "setting.h"
#include "sessiondata.h"
#include <QMainWindow>

#define BATTERY_DRAIN 1

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    int breathingRateHolder = 10;
    int challengeHolder = 1;
    int hrvTypeHolder = 7;
    Ui::MainWindow *ui;
    int curr = 0;

    Page *currPage;
    Session *mainSession;
    Menu *sessionDataMenu;

    void initGUI();
    void initPages();

    void updateBattery();

    void powerOn();
    void powerOff();
    void writeToFile();
    void readInSessionData(Menu*);

    float batteryPercent = 100;
    QPushButton *batteryEmpty;
    QPushButton *batteryFull;

    std::time_t batteryTimestamp;

    bool poweredOn = true;


private slots:
  void update();
  void upButtonPressed();
  void downButtonPressed();
  void leftButtonPressed();
  void rightButtonPressed();
  void backButtonPressed();
  void powerButtonPressed();
  void menuButtonPressed();
  void selectorButtonPressed();
  void deleteButtonPressed();
  void deleteAllButtonPressed();
  void charge();

};
#endif // MAINWINDOW_H
