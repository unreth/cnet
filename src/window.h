#ifndef WINDOW_H
#define WINDOW_H

#include <QAction>
#include <QColorDialog>
#include <QGroupBox>
#include <QLabel>
#include <QLayout>
#include <QMainWindow>
#include <QPushButton>

#include "glviewer.h"

class window : public QMainWindow {
    Q_OBJECT
public:
    window();
    virtual ~window();

    static void showStatusMessage (const QString & msg);  
    
private :
    QActionGroup * actionGroup;
    QString currentDirectory;

    glviewer * viewer;
    QLabel * imageLabel;
    QImage rayImage;

    QPushButton * rayButton;
};

#endif // WINDOW_H
