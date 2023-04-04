#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    connect(ui->upButton, &QPushButton::pressed, this, &MainWindow::upButtonPressed);
    connect(ui->downButton, &QPushButton::pressed, this, &MainWindow::downButtonPressed);
    connect(ui->leftButton, &QPushButton::pressed, this, &MainWindow::leftButtonPressed);
    connect(ui->rightButton, &QPushButton::pressed, this, &MainWindow::rightButtonPressed);
    connect(ui->backButton, &QPushButton::pressed, this, &MainWindow::backButtonPressed);
    connect(ui->powerButton, &QPushButton::pressed, this, &MainWindow::powerButtonPressed);
    connect(ui->menuButton, &QPushButton::pressed, this, &MainWindow::menuButtonPressed);
    connect(ui->selectorButton, &QPushButton::pressed, this, &MainWindow::selectorButtonPressed);
    connect(ui->coherence, &QPushButton::pressed, this, &MainWindow::coherencePressed);//Probably not necessary long term

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


    Menu *arr[5];

    arr[0] = new Menu("Menu 1", NULL, 0, ui->menuFrame);
    arr[1] = new Menu("Menu 2", NULL, 0, ui->menuFrame);
    arr[2] = new Menu("Menu 3", NULL, 0, ui->menuFrame);
    arr[3] = new Menu("Menu 4", NULL, 0, ui->menuFrame);
    arr[4] = new Menu("Menu 5", NULL, 0, ui->menuFrame);

    currMenu = new Menu("Main Menu", arr, 5, ui->menuFrame);

}

void MainWindow::upButtonPressed(){
  qDebug()<<"Up Button Pressed";
  currMenu->select(UP);
}

void MainWindow::downButtonPressed(){
  qDebug()<<"Down Button Pressed";
  currMenu->select(DOWN);
}

void MainWindow::leftButtonPressed(){
  qDebug()<<"Left Button Pressed";
}

void MainWindow::rightButtonPressed(){
  qDebug()<<"Right Button Pressed";
}

void MainWindow::backButtonPressed(){
  qDebug()<<"Back Button Pressed";
}

void MainWindow::powerButtonPressed(){
  qDebug()<<"Power Button Pressed";
}

void MainWindow::menuButtonPressed(){
  qDebug()<<"Menu Button Pressed";
}

void MainWindow::selectorButtonPressed(){
  qDebug()<<"Selector Button Pressed";
}

void MainWindow::coherencePressed(){
  qDebug()<<"Coherence Pressed";
  if(++curr%3 == 0){
    ui->coherence->setStyleSheet("background-color: red");
  }else if(curr%3==1){
    ui->coherence->setStyleSheet("background-color: blue");
  }else{
    ui->coherence->setStyleSheet("QPushButton { background-color: green }");
  }
}

MainWindow::~MainWindow()
{
    delete ui;
}
