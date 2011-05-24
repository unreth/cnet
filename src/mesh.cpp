// ---------------------------------------------------------
// mesh Class
// Author : Tamy Boubekeur (boubek@gmail.com).
// Copyright (C) 2008 Tamy Boubekeur.
// All rights reserved.
// ---------------------------------------------------------

#include "mesh.h"

using namespace std;

void mesh::renderGL() const {
    glBegin (GL_TRIANGLES);
    for (unsigned int i = 0; i < triangles.size (); i++) {
        const triangle & t = triangles[i];
        glColor3f(t.getColor(0),t.getColor(1),t.getColor(2));
        vertex v[3];
        for (unsigned int j = 0; j < 3; j++)
            v[j] = vertices[t.getVertex(j)];
        for (unsigned int j = 0; j < 3; j++){
            glNormal3f (v[j].getNormal()[0], v[j].getNormal()[1], v[j].getNormal()[2]);
            glVertex3f (v[j].getPos()[0]+center[0],v[j].getPos()[1]+center[1],v[j].getPos()[2]);
        }
    }
    glEnd ();
}


void mesh::buildNode (float x, float y, float r1, vec3Df color, vec3Df halo, vec3Df bg) {
    center[0] = x;
    center[1] = y;
    rayon = r1;
    load_node(r1,color,halo, bg);
}

void mesh::load_node (float r1, vec3Df color, vec3Df halo, vec3Df bg){
    float deuxpi = 2*3.141592;

    float r2 = 1.5*r1;
    unsigned int nvex = 100;
    unsigned int ncrl = 100; // >0 !

    clear ();

    //VERTEX
    //center
    vertices.push_back(vertex(vec3Df(0,0,0),vec3Df(0,0,1)));
    //cercles
    float r, angle;
    vec3Df normal(0,0,1);
    for(unsigned int ir = 0 ; ir< ncrl+1 ; ir++) {
        for (unsigned int iv = 0 ; iv < nvex ; iv++) {
            r = r1+(r2-r1)*ir/(float)ncrl;
            angle = iv*deuxpi/(float)nvex;
            vec3Df pos(r*cos(angle),r*sin(angle),r);
            vertices.push_back(vertex(pos,normal));
        }
    }
    //TRIANGLE
    //cercle
    for (unsigned int iv = 1; iv < nvex+1; iv++) {
        triangles.push_back(triangle(0,iv,(iv%nvex)+1,color));
    }
    //bords
    float a;
    for (unsigned int ir = 0 ; ir < ncrl ; ir++) {
        for (unsigned int iv = 0; iv < nvex; iv++) {
            a = ir/(float(ncrl));
            triangles.push_back(triangle(ir*nvex+iv+1,(ir+1)*nvex+iv+1,(ir+1)*nvex+((iv+1)%nvex)+1,               (1-a)*halo + a*bg));
            triangles.push_back(triangle(ir*nvex+iv+1,(ir+1)*nvex+((iv+1)%nvex)+1,ir*nvex+((iv+1)%nvex)+1,        (1-a)*halo + a*bg));
        }
    }
}
