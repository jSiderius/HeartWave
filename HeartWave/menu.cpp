#include "menu.h"

Menu::Menu(std::string n, Menu **arr, int arrSize, QWidget *parent) : numMenus(arrSize), subMenus(arr), name(QString::fromStdString(n))
{
  buttonSelected = 0;
  menuSelected = 0;

  for(int i = 0; i < NUM_BUTTONS; i++){
    buttons[i] = new QPushButton(parent);
    buttons[i]->setGeometry(0, i * 192/NUM_BUTTONS, 451, 192/NUM_BUTTONS);
  }
  for(int i = 0; i < numMenus; i++){
    subMenus[i]->setParent(this);
  }
  renderButtons();
  select(UP);
}

void Menu::select(direction dir){
      setColor(buttons[buttonSelected], QColor(238,238,238,255));

      if(dir == UP && menuSelected != 0){
        menuSelected--;
        if(buttonSelected != 0) buttonSelected--;
      }else if(dir == DOWN && menuSelected != numMenus - 1){
        menuSelected++;
        if(buttonSelected != NUM_BUTTONS-1) buttonSelected++;
      }

      setColor(buttons[buttonSelected], QColor(255,196,0,255));
      renderButtons();
}

void Menu::renderButtons(){
  int start = menuSelected - buttonSelected;

  for(int i = start; i < start+NUM_BUTTONS; i++){

    if(numMenus <= i){
      buttons[i-start]->hide(); //setText("");
      continue;
    }
    qDebug()<<name<<" start: "<<start<<" i: "<<i;
    buttons[i-start]->setText(subMenus[i]->getName());
    buttons[i-start]->show();
  }
}

void Menu::derender(){
  for(int i = 0; i < NUM_BUTTONS; i++){
    buttons[i]->hide();
  }
}

void Menu::setColor(QWidget* widget, QColor col){
  QPalette pal = widget->palette();
  pal.setColor(QPalette::Button, col);
  widget->setPalette(pal);
}

void Menu::setParent(Menu* p){
  parentMenu = p;
  derender();
}

Menu* Menu::click(){
  derender();
  subMenus[menuSelected]->renderButtons();
  return subMenus[menuSelected];
}

Menu* Menu::back(){
  if(parentMenu == NULL) return this;
  derender();
  parentMenu->renderButtons();
  return parentMenu;
}

Menu* Menu::mainMenu(){

  if(parentMenu == NULL){
    renderButtons();
    return this;
  }
  derender();
  return parentMenu->mainMenu();
}
