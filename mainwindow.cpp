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
  connect(ui->deleteButton, &QPushButton::pressed, this, &MainWindow::deleteButtonPressed);
  connect(ui->deleteAllButton, &QPushButton::pressed, this, &MainWindow::deleteAllButtonPressed);
  // connect(ui->coherence, &QPushButton::pressed, this, &MainWindow::coherencePressed);//Probably not necessary long term

  ui->upButton->setIcon(QIcon(":/images/upArrow.png"));
  ui->downButton->setIcon(QIcon(":/images/downArrow.png"));
  ui->leftButton->setIcon(QIcon(":/images/leftArrow.png"));
  ui->rightButton->setIcon(QIcon(":/images/rightArrow.png"));
  ui->powerButton->setIcon(QIcon(":/images/powerButton.png"));
  ui->backButton->setIcon(QIcon(":/images/backButton.png"));
  ui->menuButton->setIcon(QIcon(":/images/menuButton.png"));
  ui->deleteButton->setIcon(QIcon(":/images/delete.png"));
  ui->deleteAllButton->setIcon(QIcon(":/images/deleteAll.png"));

  ui->upButton->setIconSize(QSize(32,32));
  ui->downButton->setIconSize(QSize(32,32));
  ui->leftButton->setIconSize(QSize(32,32));
  ui->rightButton->setIconSize(QSize(32,32));
  ui->powerButton->setIconSize(QSize(32,32));
  ui->backButton->setIconSize(QSize(32,32));
  ui->menuButton->setIconSize(QSize(32,32));
  ui->deleteButton->setIconSize(QSize(32,32));
  ui->deleteAllButton->setIconSize(QSize(32,32));

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

void MainWindow::initPages(){

  Page **arr = new Page*[MAX_ARR];
  Page **settings = new Page*[MAX_ARR];

  int *intArr = new int[30];
  int *typeArr = new int[7];
  QString*stringArr = new QString[30];
  QString*typeNameArr = new QString[7];
  for(int i = 1; i<8; i++){
      //typeNameArr[i-1] = QString::number(i);
      typeArr[i-1] = i;
  }
  typeNameArr[0] = "Normal, High Coherence";
  typeNameArr[1] = "High Amplitude, High Coherence";
  typeNameArr[2] = "Low Amplitude, High Coherence";
  typeNameArr[3] = "High-Mid Coherence";
  typeNameArr[4] = "Mid Coherence";
  typeNameArr[5] = "Low-Mid Coherence";
  typeNameArr[6] = "Low Coherence";
  for(int i = 1; i < 31; i++){
    intArr[i-1] = i;
    stringArr[i-1] = QString::number(i);
  }
  QString*challNameArr = new QString[4];
  int *challArr = new int[4];
  for(int i=1; i<5; i++){
      challArr[i-1] = i;
      challNameArr[i-1] = QString::number(i);
  }
  settings[0] = new Setting<int>("Breath Pacer Setting", breathingRateHolder, intArr, 30, stringArr, ui->menuFrame);
  settings[1] = new Setting<int>("HRV Mode", hrvTypeHolder, typeArr, 7, typeNameArr, ui->menuFrame);
  settings[2] = new Setting<int>("Challenge Level", challengeHolder, challArr, 4, challNameArr, ui->menuFrame);

  Page **arr1 = new Page*[MAX_ARR];
  sessionDataMenu = new Menu("Log/History", arr1, 0, true, ui->menuFrame);
  mainSession = new Session("Session", sessionDataMenu, breathingRateHolder, ui->menuFrame, hrvTypeHolder, challengeHolder);

  arr[0] = mainSession;
  arr[1] = new Menu("Settings", settings, 3, false, ui->menuFrame);
  arr[2] = sessionDataMenu;
  currPage = new Menu("Main Menu", arr, 3, false, ui->menuFrame);

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

void MainWindow::deleteButtonPressed(){
  currPage->remove();
}

void MainWindow::deleteAllButtonPressed(){
  currPage->removeAll();
}

void MainWindow::charge(){
  batteryPercent = 100;
  batteryFull->setGeometry(35, 20.0,20, BATTERY_HEIGHT);
  batteryFull->setStyleSheet("background-color: green; border: 1px solid black; border-radius: 2px;");
}

void MainWindow::writeToFile(){
  char buff[200];
  getcwd(buff, 200);
  QFile file(QString::fromStdString(buff)+"/data.txt");
  file.open(QIODevice::WriteOnly | QIODevice::Truncate);
  file.close();
  sessionDataMenu->writeToFile();
}

void MainWindow::readInSessionData(Menu *sessionMenu){
  char buff[200];
  getcwd(buff, 200);
  QFile file(QString::fromStdString(buff)+"/data.txt");
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

    sessionMenu->add(new SessionData("Session Data" + std::to_string(++j), dataStrings.count()-3, dataArr, cohStrings.count()-1, cohArr, ui->menuFrame));
  }
}

MainWindow::~MainWindow()
{
    delete ui;
}
