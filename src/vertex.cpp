// *********************************************************
// vertex Class
// Author : Tamy Boubekeur (boubek@gmail.com).
// Copyright (C) 2008 Tamy Boubekeur.
// All rights reserved.
// *********************************************************

#include "vertex.h"

using namespace std;

static const unsigned int SIZE_OF_VERTEX = 10;

ostream & operator<< (ostream & output, const vertex & v) {
    output << v.getPos () << endl << v.getNormal ();
    return output;
}

void vertex::interpolate (const vertex & u, const vertex & v, float alpha) {
    setPos (vec3Df::interpolate (u.getPos (), v.getPos (), alpha));
    vec3Df normal = vec3Df::interpolate (u.getNormal (), v.getNormal (), alpha);
    normal.normalize ();
    setNormal (normal);
}

// ------------------------------------
// Static Members Methods.
// ------------------------------------

void vertex::computeAveragePosAndRadius (std::vector<vertex> & vertices, 
                                         vec3Df & center, float & radius) {
    center = vec3Df (0.0, 0.0, 0.0);
    for (unsigned int i = 0; i < vertices.size (); i++)
        center += vertices[i].getPos ();
    center /= float (vertices.size ());
    radius = 0.0;
    for (unsigned int i = 0; i < vertices.size (); i++) {
        float vDistance = vec3Df::distance (center, vertices[i].getPos ());
        if (vDistance > radius)
            radius = vDistance;
    }
}

void vertex::scaleToUnitBox (vector<vertex> & vertices, 
                             vec3Df & center, float & scaleToUnit) {
    computeAveragePosAndRadius (vertices, center, scaleToUnit);
    for (unsigned int i = 0; i < vertices.size (); i++) 
        vertices[i].setPos (vec3Df::segment (center, vertices[i].getPos ()) / scaleToUnit);
}

void vertex::normalizeNormals (vector<vertex> & vertices) {
    for (std::vector<vertex>::iterator it = vertices.begin (); 
         it != vertices.end (); 
         it++) {
        vec3Df n = it->getNormal ();
        if (n != vec3Df (0.0, 0.0, 0.0)) {
            n.normalize ();
            it->setNormal (n);
        }
    }    
}

