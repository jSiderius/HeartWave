#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    srand(time(nullptr));

    initGUI();
    initPages();

    batteryTimestamp = time(NULL);

    QTimer *timer = new QTimer(this);
    timer->setInterval(16);
    connect(timer, SIGNAL(timeout()), this, SLOT(update()));
    timer->start();

}

void MainWindow::initGUI(){
  connect(ui->upButton, &QPushButton::pressed, this, &MainWindow::upButtonPressed);
  connect(ui->downButton, &QPushButton::pressed, this, &MainWindow::downButtonPressed);
  connect(ui->leftButton, &QPushButton::pressed, this, &MainWindow::leftButtonPressed);
  connect(ui->rightButton, &QPushButton::pressed, this, &MainWindow::rightButtonPressed);
  connect(ui->backButton, &QPushButton::pressed, this, &MainWindow::backButtonPressed);
  connect(ui->powerButton, &QPushButton::pressed, this, &MainWindow::powerButtonPressed);
  connect(ui->menuButton, &QPushButton::pressed, this, &MainWindow::menuButtonPressed);
  connect(ui->selectorButton, &QPushButton::pressed, this, &MainWindow::selectorButtonPressed);
  // connect(ui->coherence, &QPushButton::pressed, this, &MainWindow::coherencePressed);//Probably not necessary long term

  ui->upButton->setIcon(QIcon(":/images/upArrow.png"));
  ui->downButton->setIcon(QIcon(":/images/downArrow.png"));
  ui->leftButton->setIcon(QIcon(":/images/leftArrow.png"));
  ui->rightButton->setIcon(QIcon(":/images/rightArrow.png"));
  ui->powerButton->setIcon(QIcon(":/images/powerButton.png"));
  ui->backButton->setIcon(QIcon(":/images/backButton.png"));
  ui->menuButton->setIcon(QIcon(":/images/menuButton.png"));

  ui->upButton->setIconSize(QSize(32,32));
  ui->downButton->setIconSize(QSize(32,32));
  ui->leftButton->setIconSize(QSize(32,32));
  ui->rightButton->setIconSize(QSize(32,32));
  ui->powerButton->setIconSize(QSize(32,32));
  ui->backButton->setIconSize(QSize(32,32));
  ui->menuButton->setIconSize(QSize(32,32));

  ui->selectorButton->setStyleSheet("QPushButton { border-radius: 15px; background-color: rgb(0,0,0); }");

  batteryEmpty = new QPushButton(this);
  batteryFull = new QPushButton(this);

  float endA = BATTERY_HEIGHT * (100.0 - batteryPercent) / 100.0;
  batteryEmpty->setGeometry(35, 20, 20, endA);
  batteryFull->setGeometry(35, 20.0+endA,20, BATTERY_HEIGHT * batteryPercent / 100.0);

  QString eStr = batteryPercent == 0 ? "background-color: white; border: 1px solid black; border-radius: 2px;" : "background-color: white; border: 1px solid black; border-bottom-left-radius: 0px; border-bottom-right-radius: 0px; border-top-left-radius: 2px; border-top-right-radius: 2px;";
  QString fStr = batteryPercent == 100 ? "background-color: green; border: 1px solid black; border-radius: 2px;" : "background-color: green; border: 1px solid black; border-top-left-radius: 0px; border-top-right-radius: 0px; border-bottom-left-radius: 2px; border-bottom-right-radius: 2px;";
  batteryEmpty->setStyleSheet(eStr);
  batteryFull->setStyleSheet(fStr);
  connect(batteryEmpty, &QPushButton::pressed, this, &MainWindow::charge);
  connect(batteryFull, &QPushButton::pressed, this, &MainWindow::charge);
}

//Kind of a mess right now
//If you want to add to a menu, it needs an empty array passed
void MainWindow::initPages(){

  Page **arr = new Page*[MAX_ARR];
  Page **subArr = new Page*[MAX_ARR];
  subArr[0] = new Menu("Sub Menu 1", NULL, 0, ui->menuFrame);
  subArr[1] = new Menu("Sub Menu 2", NULL, 0, ui->menuFrame);

  Page **arr1 = new Page*[MAX_ARR];
  sessionDataMenu = new Menu("Log/History", arr1, 0, ui->menuFrame);
  mainSession = new Session("Start New Session",sessionDataMenu, ui->menuFrame);

  arr[0] = mainSession;
  arr[1] = new Menu("Settings", NULL, 0, ui->menuFrame);
  arr[2] = sessionDataMenu; 
  currPage = new Menu("Main Menu", arr, 3, ui->menuFrame);

  readInSessionData(sessionDataMenu);
}

void MainWindow::update(){
  mainSession->update();
  updateBattery();
}

void MainWindow::updateBattery(){
  if(abs(difftime(batteryTimestamp, time(NULL))) > BATTERY_DRAIN && poweredOn){
    batteryTimestamp = time(NULL);
    batteryPercent = batteryPercent - 10 > 0 ? batteryPercent - 10 : 0;

    float endA = BATTERY_HEIGHT * (100.0 - batteryPercent) / 100.0;
    batteryEmpty->setGeometry(35, 20, 20, endA);
    batteryFull->setGeometry(35, 20.0+endA,20, BATTERY_HEIGHT * batteryPercent / 100.0);

    QString eStr = batteryPercent == 0 ? "background-color: white; border: 1px solid black; border-radius: 2px;" : "background-color: white; border: 1px solid black; border-bottom-left-radius: 0px; border-bottom-right-radius: 0px; border-top-left-radius: 2px; border-top-right-radius: 2px;";
    QString fStr;
    if(batteryPercent == 100){
      fStr = "background-color: green; border: 1px solid black; border-radius: 2px;";
    }else if(batteryPercent <= 30){
      fStr = "background-color: red; border: 1px solid black; border-top-left-radius: 0px; border-top-right-radius: 0px; border-bottom-left-radius: 2px; border-bottom-right-radius: 2px;";
    }else{
      fStr = "background-color: green; border: 1px solid black; border-top-left-radius: 0px; border-top-right-radius: 0px; border-bottom-left-radius: 2px; border-bottom-right-radius: 2px;";
    }
    batteryEmpty->setStyleSheet(eStr);
    batteryFull->setStyleSheet(fStr);
  }
  if(batteryPercent == 0) powerOff();

}

void MainWindow::powerOff(){
  poweredOn = false;
  currPage->derender();
  mainSession->stopSession();
  writeToFile();
}

void MainWindow::powerOn(){
  if(batteryPercent == 0) return;
  poweredOn = true;
  menuButtonPressed();
}

void MainWindow::upButtonPressed(){
  if(!poweredOn)  return;
  currPage->select(UP);
}

void MainWindow::downButtonPressed(){
  if(!poweredOn)  return;
  currPage->select(DOWN);
}

void MainWindow::leftButtonPressed(){
  if(!poweredOn)  return;
  currPage->select(LEFT);
}

void MainWindow::rightButtonPressed(){
  if(!poweredOn)  return;
  currPage->select(RIGHT);
}

void MainWindow::backButtonPressed(){
  if(!poweredOn)  return;
  currPage = currPage->back();
}

void MainWindow::powerButtonPressed(){
  poweredOn ? powerOff() : powerOn();
}

void MainWindow::menuButtonPressed(){
  if(!poweredOn)  return;
  currPage = currPage->mainPage();
}

void MainWindow::selectorButtonPressed(){
  if(!poweredOn)  return;
  currPage = currPage->click();
}

void MainWindow::charge(){
  batteryPercent = 100;
  batteryFull->setGeometry(35, 20.0,20, BATTERY_HEIGHT);
  batteryFull->setStyleSheet("background-color: green; border: 1px solid black; border-radius: 2px;");
}

void MainWindow::writeToFile(){
  char buff[200];
  getcwd(buff, 200);
  QFile file(QString::fromStdString(buff)+"/../HeartWave/data.txt");
  file.open(QIODevice::WriteOnly);
  file.close();
  sessionDataMenu->writeToFile();
}

void MainWindow::readInSessionData(Menu *sessionMenu){
  char buff[200];
  getcwd(buff, 200);
  QFile file(QString::fromStdString(buff)+"/../HeartWave/data.txt");
  file.open(QIODevice::ReadOnly | QIODevice::Text);

  QByteArray fileData = file.readAll();
  QStringList sessions = QString(fileData).split('$');

  int j = 0;
  foreach(QString session, sessions){
    QStringList arrayStrings = QString(session).split('&');
    if(arrayStrings.count()!=2)continue;

    QStringList dataStrings = QString(arrayStrings[0]).split(',');
    QStringList cohStrings = QString(arrayStrings[1]).split(',');

    float *dataArr = new float[dataStrings.count()];
    float *cohArr = new float[cohStrings.count()];

    int i = 0;
    foreach(QString val, dataStrings){
      if(val!="")dataArr[i++] = val.toFloat();
    }
    i = 0;
    foreach(QString val, cohStrings){
      cohArr[i++] = val.toFloat();
    }

    qDebug()<<cohStrings;
    qDebug()<<"\n\n";
    sessionMenu->add(new SessionData("Session Data" + std::to_string(++j), dataStrings.count()-3, dataArr, cohStrings.count()-1, cohArr, ui->menuFrame));
  }
}

MainWindow::~MainWindow()
{
    delete ui;
}
