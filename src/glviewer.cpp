#include "glviewer.h"

using namespace std;

static const GLuint OpenGLLightID[] = {GL_LIGHT0, GL_LIGHT1, GL_LIGHT2, GL_LIGHT3, GL_LIGHT4, GL_LIGHT5, GL_LIGHT6, GL_LIGHT7};

glviewer::glviewer () : QGLViewer () {
    renderingMode = Smooth;
    moving = -1;
}

glviewer::~glviewer () {
}


void glviewer::setRenderingMode (bool m) {
    renderingMode = static_cast<RenderingMode>((int)m);
    updateGL ();
}

void glviewer::keyPressEvent (QKeyEvent * /*event*/)   {}
void glviewer::keyReleaseEvent (QKeyEvent * /*event*/) {
}
void glviewer::mousePressEvent(QMouseEvent * e) {
    if(e->button()==Qt::LeftButton){
        QPoint point(e->x(),e->y());
        bool found;
        Vec v = camera()->pointUnderPixel(point,found);
        for(unsigned int i=0; i<nodes.size(); i++){
            if(nodes[i].intersect(v.x,v.y)){
                oldx = nodes[i].getCenter(0)-v.x;
                oldy = nodes[i].getCenter(1)-v.y;
                moving = i;
                break;
            }
        }
    }
}
void glviewer::mouseMoveEvent(QMouseEvent * e) {
    if(moving!=-1){
        QPoint point(e->x(),e->y());
        bool found;
        Vec v = camera()->pointUnderPixel(point,found);
        nodes[moving].setCenter(v.x+oldx,v.y+oldy);
    }
}
void glviewer::mouseReleaseEvent(QMouseEvent *) {
    moving = -1;
}

void glviewer::init() {
    bg = vec3Df(1,1,1);
    glClearColor (bg[0],bg[1],bg[2],0);

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(-1, 1, -1, 1, -1, 1);


    glEnable (GL_COLOR_MATERIAL);

    setSceneRadius (5);
    showEntireScene ();
    startAnimation();   //automatic update!

    mesh m = mesh();
    m.buildNode(1,1,0.3,vec3Df(1,1,1),vec3Df(0.5,0.5,0.5),bg);
    nodes.push_back(m);
}

void glviewer::draw () {
    for(unsigned int i=0; i<nodes.size(); i++)
        nodes.at(i).renderGL();
}
