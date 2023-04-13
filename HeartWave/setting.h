#ifndef SETTING_H
#define SETTING_H

#include "defs.h"
#include "page.h"

template <typename T>
class Setting : public Page
{
  public:
      Setting(std::string, T&, T*, int, QString *, QWidget*);
      Page* click();
      void render();
      void derender();
      void select(direction);
      void print();

  private:
    T& value;
    T* options;
    QString *strings;
    QPushButton *buttons[NUM_BUTTONS];

    int numSettings;
    int settingSelected;
    int buttonSelected;
};

#endif // SETTING_H
