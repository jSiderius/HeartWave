#ifndef MENU_H
#define MENU_H

#include "defs.h"

class Menu
{

  public:
      Menu(std::string, Menu**, int, QWidget*);

      void select(direction);

      QString getName(){ return name; }
      void setParent(Menu*);
      Menu* click();
      Menu* back();
      Menu* mainMenu();


  private:
    void setColor(QWidget*, QColor);
    void renderButtons();
    void derender();

    Menu *parentMenu = NULL;
    Menu **subMenus;

    QPushButton *buttons[NUM_BUTTONS];

    int numMenus;
    int menuSelected;
    int buttonSelected;

    QString name;

};

#endif // MENU_H
