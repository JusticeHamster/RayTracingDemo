#include "openglwidget.h"
#include "opengl_header.hpp"

#include <QDebug>
#include <iostream>

using namespace std;

OpenGLWidget::OpenGLWidget(QWidget *parent) : QGLWidget(parent) {
}

void OpenGLWidget::initializeGL() {
    glClearColor(1.0, 1.0, 1.0, 0.0);
    // 着色方式选择
    glShadeModel(GL_SMOOTH);
    glClearDepth(1.0);
    glEnable(GL_DEPTH_TEST);
}

void OpenGLWidget::resizeGL(int w, int h) {
    glViewport(0, 0, w, h);
    // GL_PROJECTION 投影, GL_MODELVIEW 模型视图, GL_TEXTURE 纹理.
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    // 视角的角度（眼睛睁开大小），窗口横纵比例，近处截面，远处截面
    gluPerspective(45.0, static_cast<double>(w) / h, 0.1, 100);
    gluLookAt(-3, 2, -10, 0, 0, 0, 0, 1, 0);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    updateGL();
}

void OpenGLWidget::paintGL() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); // 清除缓冲区
    glLoadIdentity(); // 恢复初始坐标系

    glMatrixMode(GL_MODELVIEW); // 设置投影矩阵
    ldr.get_scene("base").draw();
}
