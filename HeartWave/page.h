#ifndef PAGE_H
#define PAGE_H

#include "defs.h"

class Page
{
  public:
      Page(std::string, QWidget*);
      virtual ~Page(){}

      virtual void select(direction) = 0;
      QString getName(){ return name; }
      void setParent(Page*);

      virtual Page* click() = 0;
      Page* back();
      Page* mainPage();

      virtual void render() = 0;
      virtual void derender() = 0;

      virtual void writeToFile(){};

      void setColor(QPushButton*, QColor);

  protected:
    Page *parentPage = NULL;
    QString name;

};

#endif // PAGE_H
