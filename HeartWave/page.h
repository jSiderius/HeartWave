#ifndef PAGE_H
#define PAGE_H

#include "defs.h"

class Page
{
  public:
      Page(std::string, QWidget*);
      virtual ~Page(){}

      QString getName(){ return name; }
      void setParent(Page*);

      Page* back();
      Page* mainPage();

      virtual Page* click(){ return this; }
      virtual void render(){}
      virtual void derender(){}
      virtual void select(direction){}
      virtual void remove(){}
      virtual void removeAll(){}
      virtual void writeToFile(){}
      virtual void print(){}

      void setColor(QPushButton*, QColor);

  protected:
    Page *parentPage = NULL;
    QString name;

};

#endif // PAGE_H
