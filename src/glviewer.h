// *********************************************************
// OpenGL Viewer Class, based on LibQglviewer, compatible
// with most hardware (OpenGL 1.2).
// Author : Tamy Boubekeur (boubek@gmail.com).
// Copyright (C) 2010 Tamy Boubekeur.
// All rights reserved.
// *********************************************************

#ifndef GLVIEWER_H
#define GLVIEWER_H

#include <QGLViewer/qglviewer.h>
#include <vector>
#include <string>
#include <iostream>
#include <cstdlib>
#include <cstdio>
#include <cassert>
#include <string>
#include <QMouseEvent>
#include <QGLViewer/vec.h>

#include "mesh.h"

using namespace std;
using namespace qglviewer;

class glviewer : public QGLViewer  {
    Q_OBJECT
public:
    
    typedef enum {Flat=0, Smooth=1} RenderingMode;
    
    glviewer ();
    virtual ~glviewer ();
    
    inline int getRenderingMode () const { return renderingMode; }
    
    class Exception  {
    public:
        Exception (const std::string & msg) : message ("[glviewer]"+msg) {}
        virtual ~Exception () {}
        const std::string & getMessage () const { return message; }
    private:
        std::string message;
    }; 
     
public slots :
    void setRenderingMode (bool m);
    
protected :
    void init();
    void draw ();

    virtual void keyPressEvent ( QKeyEvent * event );
    virtual void keyReleaseEvent ( QKeyEvent * event );
    virtual void mousePressEvent( QMouseEvent * event );
    virtual void mouseMoveEvent( QMouseEvent * event );
    virtual void mouseReleaseEvent( QMouseEvent * event );

private:
    RenderingMode renderingMode;

    vector<mesh> nodes;
    vector<mesh> links;

    float oldx,oldy;
    int moving;
    vec3Df bg;
};

#endif // GLVIEWER_H
