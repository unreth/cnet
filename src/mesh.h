// ---------------------------------------------------------
// mesh Class
// Author : Tamy Boubekeur (boubek@gmail.com).
// Copyright (C) 2008 Tamy Boubekeur.
// All rights reserved.
// ---------------------------------------------------------

#ifndef MESH_H
#define MESH_H

#if __APPLE__
#	include <GLUT/glut.h>
#else
#	include <GL/glut.h>
#endif

#include <vector>
#include <string>
#include <algorithm>
#include <iostream>
#include <fstream>
#include <sstream>
#include <cmath>

#include "vertex.h"
#include "triangle.h"

class mesh {
public:
    inline mesh ()                                                                                                                      {}
    inline mesh (const std::vector<vertex> & v)                                  : vertices (v)                                         {}
    inline mesh (const std::vector<vertex> & v, const std::vector<triangle> & t) : vertices (v),             triangles (t)              {}
    inline mesh (const mesh & mesh)                                              : vertices (mesh.vertices), triangles (mesh.triangles), rayon(mesh.rayon) { center[0]=mesh.center[0]; center[1]=mesh.center[1]; }
        
    inline virtual ~mesh () {}

    inline mesh & operator= (const mesh & im) { vertices=im.vertices; triangles=im.triangles; center[0]=im.center[0]; center[1]=im.center[1]; rayon=im.rayon; return (*this); }

    std::vector<vertex> & getVertices () { return vertices; }
    const std::vector<vertex> & getVertices () const { return vertices; }
    std::vector<triangle> & getTriangles () { return triangles; }
    const std::vector<triangle> & getTriangles () const { return triangles; }
    inline float getCenter(unsigned int i) { return center[i]; }
    inline void setCenter(float x,float y){ center[0]=x; center[1]=y; }

    inline void clear ()         { clearTopology (); clearGeometry (); }
    inline void clearGeometry () { vertices.clear ();                  }
    inline void clearTopology () { triangles.clear ();                 }
    
    void renderGL() const;
    inline float getx()     { return center[0];}
    inline float gety()     { return center[1];}
    inline float getrayon() { return rayon; }
    inline bool intersect(float x,float y) {
        if(abs(x-center[0])<rayon && abs(y-center[1])<rayon)
            return true;
        return false;
    }

    void buildNode (float x, float y, float r1, vec3Df color, vec3Df halo, vec3Df bg);
    void load_node (float,vec3Df color,vec3Df halo, vec3Df bg);

    class Exception {
    private: 
        std::string msg;
    public:
        Exception (const std::string & msg) : msg ("[mesh Exception]" + msg) {}
        virtual ~Exception () {}
        inline const std::string & getMessage () const { return msg; }
    };

private:
    std::vector<vertex> vertices;
    std::vector<triangle> triangles;

    float center[2];
    float rayon;
};

#endif // MESH_H
