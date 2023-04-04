#include "menu.h"

Menu::Menu(std::string name, Menu **arr, int arrSize, QWidget *parent) : numMenus(arrSize), subMenus(arr), name(QString::fromStdString(name))
{
  selected = 0;
  buttons[0] = new QPushButton(parent);
  buttons[1] = new QPushButton(parent);
  buttons[2] = new QPushButton(parent);

  for(int i = 0; i < numMenus; i++){
    qDebug()<<(subMenus[i]->getName());
  }

}

void Menu::select(direction dir){
      setColor(buttons[selected], QColor(238,238,238,255));

      if(dir == UP && selected != 0){
        selected--;//counter intuitive but menu 0 is at the top
      }else if(dir == DOWN && selected != 2){//MIGHT NEED A FIX TO CORRESPOND TO MENUS
        selected++;
      }

      setColor(buttons[selected], QColor(255,196,0,255));
      renderButtons();
}

void Menu::renderButtons(){
  qDebug()<<"Rendering Buttons for "<<name;
  for(int i = 0; i < 3; i++){

    if(numMenus < i)  break;
    buttons[i]->setGeometry(0, i * 64, 451, 64);
    // qDebug()<<i<<subMenus[0]->getName();
    // buttons[i]->setText(subMenus[i+selected]->getName());
  }

  for(int i = 0; i < numMenus; i++){
    // qDebug()<<subMenus[i]->getName();
  }
}

void Menu::setColor(QWidget* widget, QColor col){
  QPalette pal = widget->palette();
  pal.setColor(QPalette::Button, col);
  widget->setPalette(pal);
}
