#ifndef MENU_H
#define MENU_H

#include "defs.h"

class Menu
{

  public:
      Menu(std::string, Menu**, int, QWidget*);

      void select(direction);

      QString getName(){ return name; }


  private:
    void setColor(QWidget*, QColor);
    void renderButtons();

    Menu *parent;
    Menu **subMenus;

    QPushButton *buttons[3];

    int numMenus;
    int selected;

    QString name;

};

#endif // MENU_H
