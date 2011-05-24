// *********************************************************
// vertex Class
// Author : Tamy Boubekeur (boubek@gmail.com).
// Copyright (C) 2008 Tamy Boubekeur.
// All rights reserved.
// *********************************************************

#ifndef VERTEX_H
#define VERTEX_H

#include <iostream>
#include <QGLViewer/qglviewer.h>

#include "vec3D.h"

#define PI 3.141592

class vertex {
public:
    inline vertex () :                                          pos (vec3Df (0.0,0.0,0.0)), normal (vec3Df (0.0, 0.0, 1.0)), marked (false),    id (-1) {}
    inline vertex (const vec3Df & pos) :                        pos (pos),                  normal (vec3Df (0.0, 0.0, 1.0)), marked (false),    id (-1) {}
    inline vertex (const vec3Df & pos, const vec3Df & normal) : pos (pos),                  normal (normal),                 marked (false),    id (-1) {}
    inline vertex (const vertex & v) :                          pos (v.pos),                normal (v.normal),               marked (v.marked), id (-1) {}
    inline virtual ~vertex () {}

    inline void calcangles () {
        //theta
        if(pos[2]>0)                    theta = atan(sqrt(pos[0]*pos[0] + pos[1]*pos[1])/pos[2]);
        else if(pos[2]<0)               theta = atan(sqrt(pos[0]*pos[0] + pos[1]*pos[1])/pos[2]) + PI;
        else                            theta = PI/2;
        theta *= 180/PI;

        //phi
        if(pos[0]>0){
            if(pos[1]<0)                phi = atan(pos[1]/pos[0]) + 2*PI;
            else                        phi = atan(pos[1]/pos[0]);
        }
        else if(pos[0]<0)               phi = atan(pos[1]/pos[0]) + PI;
        else{
            if(pos[1]<0)                phi = -PI/2;
            else                        phi = PI/2;
        }
        phi *= 180/PI;
    }

    inline vertex & operator= (const vertex & vertex) {
        pos = vertex.pos;
        normal = vertex.normal;
        marked = vertex.marked;
        id = -1;
        return (*this);
    }

    inline const vec3Df & getPos () const { return pos; }
    inline const vec3Df & getNormal () const { return normal; }  
    inline bool isMarked () const { return marked; }
    inline int getId () const { return id; }
    inline void setPos (const vec3Df & newPos) { pos = newPos; }
    inline void setNormal (const vec3Df & newNormal) { normal = newNormal; }
    inline void mark () { marked = true; }
    inline void unmark () { marked = false; }
    inline void setId (int newId) { id = newId; } 
    inline bool operator== (const vertex & v) { return (v.pos == pos && v.normal == normal); }

    void interpolate (const vertex & u, const vertex & v, float alpha = 0.5);
    static void computeAveragePosAndRadius (std::vector<vertex> & vertices, vec3Df & center, float & radius);
    static void scaleToUnitBox (std::vector<vertex> & vertices, vec3Df & center, float & scaleToUnitBox);
    static void normalizeNormals (std::vector<vertex> & vertices);


private:
    vec3Df pos;
    vec3Df normal;
    bool marked;
    int id;

    float phi;
    float theta;
};

extern std::ostream & operator<< (std::ostream & output, const vertex & v);

#endif // VERTEX_H

