#include "page.h"

Page::Page(std::string n, QWidget *parent) : name(QString::fromStdString(n))
{

}

Page* Page::mainPage(){
  if(parentPage == NULL){
    render();
    return this;
  }
  derender();
  return parentPage->mainPage();
}

Page* Page::back(){
  if(parentPage == NULL) return this;
  derender();
  parentPage->render();
  return parentPage;
}

void Page::setParent(Page* p){
  parentPage = p;
  derender();
}

void Page::setColor(QPushButton* widget, QColor col){
  QPalette pal = widget->palette();
  pal.setColor(QPalette::Button, col);
  widget->setPalette(pal);
}
