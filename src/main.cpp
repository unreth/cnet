#include <QApplication>
#include <QPlastiqueStyle>

#include "window.h"

using namespace std;

int main (int argc, char **argv)
{
  QApplication gmopen (argc, argv);
  QApplication::setStyle (new QPlastiqueStyle);
  window * w = new window ();
  w->setWindowTitle ("cnet");
  w->showMaximized ();
  w->show();
  
  return gmopen.exec ();
}
