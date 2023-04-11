#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "defs.h"
#include "menu.h"
#include "session.h"
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
  void charge();

};
#endif // MAINWINDOW_H
