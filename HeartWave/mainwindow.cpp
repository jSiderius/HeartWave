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
}

//Kind of a mess right now
//If you want to add to a menu, it needs an empty array passed
void MainWindow::initPages(){
  int *cohData = new int[10];
  int *data = new int[3000];
  for(int i = 0; i < 10; i++){
    cohData[i] = rand()%3;
  }
  for(int i = 0; i < 3000; i++){
    data[i] = std::sin(i/8) * 10 + 50;
  }

  Page **arr = new Page*[MAX_ARR];
  Page **subArr = new Page*[MAX_ARR];
  subArr[0] = new Menu("Sub Menu 1", NULL, 0, ui->menuFrame);
  subArr[1] = new Menu("Sub Menu 2", NULL, 0, ui->menuFrame);

  Page **arr1 = new Page*[MAX_ARR];
  sessionDataMenu = new Menu("Log/History", arr1, 0, ui->menuFrame);
  mainSession = new Session("Start New Session",sessionDataMenu, ui->menuFrame);

  arr[0] = mainSession;
  arr[1] = new Menu("Settings", NULL, 0, ui->menuFrame);
  arr[2] = sessionDataMenu; //Read in saved data & write a session display page class which stores each session
  // arr[3] = new SessionData("Session Data", 3000, data, 10, cohData, ui->menuFrame);
  // arr[3] = new Menu("Sub Menus", subArr, 2, ui->menuFrame);
  currPage = new Menu("Main Menu", arr, 3, ui->menuFrame);
}

void MainWindow::update(){
  mainSession->update();
}

void MainWindow::upButtonPressed(){
  currPage->select(UP);
}

void MainWindow::downButtonPressed(){
  currPage->select(DOWN);
}

void MainWindow::leftButtonPressed(){
  currPage->select(LEFT);
}

void MainWindow::rightButtonPressed(){
  currPage->select(RIGHT);
}

void MainWindow::backButtonPressed(){
  currPage = currPage->back();
}

void MainWindow::powerButtonPressed(){
}

void MainWindow::menuButtonPressed(){
  currPage = currPage->mainPage();
}

void MainWindow::selectorButtonPressed(){
  currPage = currPage->click();
}

MainWindow::~MainWindow()
{
    delete ui;
}
