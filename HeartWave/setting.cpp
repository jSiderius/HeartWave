#include "setting.h"

template <typename T>
Setting<T>::Setting(std::string n,  T& val, T*o, int ns, QString *s, QWidget* parent) : Page(n, parent), options(o), numSettings(ns), strings(s), value(val)
{
  buttonSelected = 0;
  settingSelected = 0;

  for(int i = 0; i < NUM_BUTTONS; i++){
    buttons[i] = new QPushButton(parent);
    buttons[i]->setGeometry(0, i * 221/NUM_BUTTONS, 451, 221/NUM_BUTTONS);
  }
  render();
  select(UP);
}

template <typename T>
Page* Setting<T>::click(){
  value = options[settingSelected];
  qDebug()<<value;
  return this;
}

template <typename T>
void Setting<T>::render(){
  int start = settingSelected - buttonSelected;

  for(int i = start; i < start+NUM_BUTTONS; i++){

    if(numSettings <= i){
      buttons[i-start]->hide(); //setText("");
      continue;
    }
    buttons[i-start]->setText(strings[i]);
    buttons[i-start]->show();
  }
}

template <typename T>
void Setting<T>::derender(){
  for(int i = 0; i < NUM_BUTTONS; i++){
    buttons[i]->hide();
  }
}

template <typename T>
void Setting<T>::select(direction dir){
  setColor(buttons[buttonSelected], QColor(238,238,238,255));

  if(dir == UP && settingSelected != 0){
    settingSelected--;
    if(buttonSelected != 0) buttonSelected--;
  }else if(dir == DOWN && settingSelected != numSettings - 1){
    settingSelected++;
    if(buttonSelected != NUM_BUTTONS-1) buttonSelected++;
  }

  setColor(buttons[buttonSelected], QColor(255,196,0,255));
  render();
}

template <typename T>
void Setting<T>::print(){
  qDebug()<<"Setting";
}

template class Setting<int>;
