#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "defs.h"
#include "menu.h"
#include <QMainWindow>

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

    void initGUI();
    void initPages();

private slots:
  void upButtonPressed();
  void downButtonPressed();
  void leftButtonPressed();
  void rightButtonPressed();
  void backButtonPressed();
  void powerButtonPressed();
  void menuButtonPressed();
  void selectorButtonPressed();
  void coherencePressed();

};
#endif // MAINWINDOW_H
