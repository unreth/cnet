// *********************************************************
// triangle Class
// Author : Tamy Boubekeur (boubek@gmail.com).
// Copyright (C) 2008 Tamy Boubekeur.
// All rights reserved.
// *********************************************************

#ifndef TRIANGLE_H
#define TRIANGLE_H

#include <iostream>
#include <GL/gl.h>

#include "vec3D.h"

using namespace std;

class triangle {
public:
    inline triangle ()                                                                                        { init (0,0,0);                            }
    inline triangle (unsigned int v0, unsigned int v1, unsigned int v2)                                       { init (v0,v1,v2);                         }
    inline triangle (unsigned int v0, unsigned int v1, unsigned int v2, vec3Df color)                         { init (v0,v1,v2);    this->color = color; }
    inline triangle (const unsigned int * vp)                                                                 { init(vp[0], vp[1], vp[2]);               }
    inline triangle (const triangle & it)                                                                     { init(it.v[0],it.v[1],it.v[2]); color=it.color; }
    inline virtual ~triangle () {}
    inline triangle & operator= (const triangle & it) { init(it.v[0],it.v[1],it.v[2]); color = it.color; return (*this); }
    inline bool operator== (const triangle & t) const { return (v[0] == t.v[0] && v[1] == t.v[1] && v[2] == t.v[2] && color == t.color); }
    inline unsigned int getVertex (unsigned int i) const { return v[i]; }
    inline void setVertex (unsigned int i, unsigned int vertex) { v[i] = vertex; }
    inline bool contains (unsigned int vertex) const { return (v[0] == vertex || v[1] == vertex || v[2] == vertex); }
  
    inline float getColor (unsigned int i) const { return color[i]; }

protected:
    inline void init (unsigned int v0, unsigned int v1, unsigned int v2) {
        v[0] = v0; v[1] = v1; v[2] = v2;  
    }
  
private:
    unsigned int v[3];
    vec3Df color;
};

extern std::ostream & operator<< (std::ostream & output, const triangle & t);

#endif // TRIANGLE_H
