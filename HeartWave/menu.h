#ifndef MENU_H
#define MENU_H

#include "defs.h"
#include "page.h"

class Menu : public Page
{

  public:
      Menu(std::string, Page**, int, QWidget*);
      void add(Page *);
      void writeToFile();


  private:
    Page* click();
    void  derender();
    void  render();
    void  select(direction dir);


    Page **subPages;

    QPushButton *buttons[NUM_BUTTONS];

    int numPages;
    int pageSelected;
    int buttonSelected;



};

#endif // MENU_H
