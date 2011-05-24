#include "window.h"

using namespace std;

window::window () : QMainWindow (NULL) {
    try {
        viewer = new glviewer;
    } catch (glviewer::Exception e) {
        cerr << e.getMessage () << endl;
        exit (1);
    }
    QGroupBox * renderingGroupBox = new QGroupBox (this);
    QHBoxLayout * renderingLayout = new QHBoxLayout (renderingGroupBox);
    
    renderingLayout->addWidget (viewer);
    setCentralWidget (renderingGroupBox);
    
    setMinimumWidth (800);
    setMinimumHeight (400);
}

window::~window () {

}
