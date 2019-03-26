#include "openglwidget.h"
#include "opengl_header.h"

OpenGLWidget::OpenGLWidget(QWidget *parent) : QGLWidget(parent) {
    ;
}

void OpenGLWidget::initializeGL() {
    glClearColor(0.0, 0.0, 0.0, 0.0);
    glShadeModel(GL_SMOOTH);
    glClearDepth(1.0);
    glEnable(GL_DEPTH_TEST);
}

void OpenGLWidget::resizeGL(int w, int h) {
    glViewport(0, 0, w, h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(45.0, static_cast<double>(w) / h, 0.1, 100);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}

void OpenGLWidget::paintGL() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();

    glTranslatef(-2.0, 0.0, -6.0);
    glBegin(GL_TRIANGLES);
    glVertex3f(-1.0, 1.0, 0.0);
    glVertex3f(0.0, -1.0, 0.0);
    glVertex3f(1.0, 1.0, 0.0);
    glEnd();

    glTranslatef(4.0, 0.0, 0.0);
    glBegin(GL_QUADS);
    glVertex3f(-1.0, 1.0, 0.0);
    glVertex3f(-1.0, -1.0, 0.0);
    glVertex3f(1.0, -1.0, 0.0);
    glVertex3f(1.0, 1.0, 0.0);
    glEnd();
}
