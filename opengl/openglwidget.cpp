#include "openglwidget.h"
#include "opengl_header.hpp"
#include <QDebug>
#include <iostream>
#define PI          3.14
using namespace std;

OpenGLWidget::OpenGLWidget(QWidget *parent) : QGLWidget(parent) {
    this->R=1;
    x=-3,y=2,z=-10;
//    connect(&timer,SIGNAL(timeout()),this,SLOT(updateGL()));
//    timer.start(16);
}

void OpenGLWidget::initializeGL() {
    glClearColor(0.0, 0.0, 0.0, 0.0);
    // 着色方式选择
    glShadeModel(GL_SMOOTH);
    glClearDepth(1.0);
    glEnable(GL_DEPTH_TEST);
}

void OpenGLWidget::buttonclick(){
    gluLookAt(x,y,z, 0, 0, 0, 0, 1, 0);
    updateGL();
    qDebug() << x << y << z;
//    glutPostRedisplay();
}

void OpenGLWidget::resizeGL(int w, int h) {
    glViewport(0, 0, w, h);
    // GL_PROJECTION 投影, GL_MODELVIEW 模型视图, GL_TEXTURE 纹理.
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    // 视角的角度（眼睛睁开大小），窗口横纵比例，近处截面，远处截面
    gluPerspective(45.0, static_cast<double>(w) / h, 0.1, 100);
    gluLookAt(x,y,z, 0, 0, 0, 0, 1, 0);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    updateGL();
}


void OpenGLWidget::paintGL() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);// 清除缓冲区
    glLoadIdentity();// 恢复初始坐标系

    glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);


    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
//    drawSphere(0,0,0,R,30,30);
//    drawTetrahedron();
    drawCube();
}

// 绘制球体
// 球心坐标为（x，y，z），球的半径为radius，M，N分别表示球体的横纵向被分成多少份
void OpenGLWidget::drawSphere(GLfloat xx, GLfloat yy, GLfloat zz,
                          GLfloat radius, GLfloat M, GLfloat N)
{

    float step_z = PI / M;
    float step_xy = 2 * PI / N;
    float x[4], y[4], z[4];

    float angle_z = 0.0;
    float angle_xy = 0.0;
    int i = 0, j = 0;
    glBegin(GL_QUADS);
    for(i = 0; i < M; i++)
    {
        angle_z = i * step_z;

        for(j = 0; j < N; j++)
        {
            angle_xy = j * step_xy;

            x[0] = radius * sin(angle_z) * cos(angle_xy);
            y[0] = radius * sin(angle_z) * sin(angle_xy);
            z[0] = radius * cos(angle_z);

            x[1] = radius * sin(angle_z + step_z) * cos(angle_xy);
            y[1] = radius * sin(angle_z + step_z) * sin(angle_xy);
            z[1] = radius * cos(angle_z + step_z);

            x[2] = radius * sin(angle_z + step_z) * cos(angle_xy + step_xy);
            y[2] = radius * sin(angle_z + step_z) * sin(angle_xy + step_xy);
            z[2] = radius * cos(angle_z + step_z);

            x[3] = radius * sin(angle_z) * cos(angle_xy + step_xy);
            y[3] = radius * sin(angle_z) * sin(angle_xy + step_xy);
            z[3] = radius * cos(angle_z);
            for(int k = 0; k < 4; k++)
            {
                glColor3f(sin(angle_z), cos(angle_z), tan(angle_z));
                //glTexCoord2f(0.1f, 0.1f);
                glVertex3f(xx + x[k], yy + y[k], zz + z[k]);
            }
        }
    }
    glEnd();
}

// 绘制四面体等
void OpenGLWidget::drawTetrahedron()
{
    glBegin(GL_QUADS);
    glNormal3f(0, 0, -1);
    glColor3f(1.0, 0.0, 0.0);
    glVertex3f(-1, -1, 0);
    glColor3f(0.0, 1.0, 0.0);
    glVertex3f(-1, 1, 0);
    glColor3f(0.0, 0.0, 1.0);
    glVertex3f(1, 1, 0);
    glColor3f(1.0, 1.0, 0.0);
    glVertex3f(1, -1, 0);
    glEnd();

    glBegin(GL_TRIANGLES);
    glNormal3f(0, -1, 0.707);
    glColor3f(0.0, 1.0, 1.0);
    glVertex3f(-1, -1, 0);
    glColor3f(1.0, 0.0, 1.0);
    glVertex3f(1, -1, 0);
    glColor3f(1.0, 0.0, 1.0);
    glVertex3f(0, 0, 1.2);
    glEnd();
    glBegin(GL_TRIANGLES);
    glNormal3f(1, 0, 0.707);
    glColor3f(0.0, 1.0, 1.0);
    glVertex3f(1, -1, 0);
    glColor3f(1.0, 0.0, 1.0);
    glVertex3f(1, 1, 0);
    glColor3f(1.0, 0.0, 1.0);
    glVertex3f(0, 0, 1.2);
    glEnd();
    glBegin(GL_TRIANGLES);
    glNormal3f(0, 1, 0.707);
    glColor3f(0.0, 1.0, 1.0);
    glVertex3f(1, 1, 0);
    glColor3f(1.0, 0.0, 1.0);
    glVertex3f(-1, 1, 0);
    glColor3f(1.0, 0.0, 1.0);
    glVertex3f(0, 0, 1.2);
    glEnd();
    glBegin(GL_TRIANGLES);
    glNormal3f(-1, 0, 0.707);
    glColor3f(1.0, 0.0, 1.0);
    glVertex3f(-1, 1, 0);
    glColor3f(0.0, 1.0, 1.0);
    glVertex3f(-1, -1, 0);
    glColor3f(1.0, 0.0, 0.0);
    glVertex3f(0, 0, 1.2);
    glEnd();
}

// 绘制立方体
void OpenGLWidget::drawCube()
{
    glBegin(GL_QUAD_STRIP);         //填充凸多边形
    glColor3f(1, 0, 0);
    glVertex3f(0.0f, 0.0f, 0.0f);
    glColor3f(1, 1, 0);
    glVertex3f(0.0f, 1.0f, 0.0f);
    glColor3f(0, 1, 0);
    glVertex3f(1.0f, 0.0f, 0.0f);
    glColor3f(0, 1, 1);
    glVertex3f(1.0f, 1.0f, 0.0f);
    glColor3f(1, 0, 0);
    glVertex3f(1.0f, 0.0f, -1.0f);
    glColor3f(1, 1, 0);
    glVertex3f(1.0f, 1.0f, -1.0f);
    glColor3f(0, 1, 0);
    glVertex3f(0.0f, 0.0f, -1.0f);
    glColor3f(0, 1, 1);
    glVertex3f(0.0f, 1.0f, -1.0f);
    glColor3f(1, 0, 0);
    glVertex3f(0.0f, 0.0f, 0.0f);
    glColor3f(1, 1, 0);
    glVertex3f(0.0f, 1.0f, 0.0f);
    glEnd();
    glBegin(GL_QUAD_STRIP);
    glColor3f(0, 0, 1);
    glVertex3f(0.0f, 0.0f, 0.0f);
    glColor3f(1, 0, 1);
    glVertex3f(1.0f, 0.0f, 0.0f);
    glColor3f(0, 1, 0);
    glVertex3f(0.0f, 0.0f, -1.0f);
    glColor3f(1, 0, 0);
    glVertex3f(1.0f, 0.0f, -1.0f);
    glColor3f(1, 1, 0);
    glVertex3f(0.0f, 1.0f, 0.0f);
    glColor3f(1, 0, 1);
    glVertex3f(1.0f, 1.0f, 0.0f);
    glColor3f(0, 0, 1);
    glVertex3f(0.0f, 1.0f, -1.0f);
    glColor3f(1, 0, 0);
    glVertex3f(1.0f, 1.0f, -1.0f);
    glEnd();
}
