#include "menu.h"

Menu::Menu(std::string n, Page **arr, int arrSize, QWidget *parent) : Page(n, parent), numPages(arrSize), subPages(arr)
{
  buttonSelected = 0;
  pageSelected = 0;

  for(int i = 0; i < NUM_BUTTONS; i++){
    buttons[i] = new QPushButton(parent);
    buttons[i]->setGeometry(0, i * 192/NUM_BUTTONS, 451, 192/NUM_BUTTONS);
  }
  for(int i = 0; i < numPages; i++){
    subPages[i]->setParent(this);
  }
  render();
  select(UP);
}

void Menu::select(direction dir){
      setColor(buttons[buttonSelected], QColor(238,238,238,255));

      if(dir == UP && pageSelected != 0){
        pageSelected--;
        if(buttonSelected != 0) buttonSelected--;
      }else if(dir == DOWN && pageSelected != numPages - 1){
        pageSelected++;
        if(buttonSelected != NUM_BUTTONS-1) buttonSelected++;
      }

      setColor(buttons[buttonSelected], QColor(255,196,0,255));
      render();
}

void Menu::render(){
  int start = pageSelected - buttonSelected;

  for(int i = start; i < start+NUM_BUTTONS; i++){

    if(numPages <= i){
      buttons[i-start]->hide(); //setText("");
      continue;
    }
    buttons[i-start]->setText(subPages[i]->getName());
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

Page* Menu::click(){
  if(numPages == 0) return this;
  derender();
  subPages[pageSelected]->render();
  return subPages[pageSelected];
}
