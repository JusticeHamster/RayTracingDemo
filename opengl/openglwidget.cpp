#include "openglwidget.h"
#include "opengl_header.hpp"

OpenGLWidget::OpenGLWidget(QWidget *parent) : QGLWidget(parent), ldr(loader::instance) {
    timer = std::make_unique<QTimer>(this);
    connect(timer.get(), SIGNAL(timeout()), this, SLOT(timer_update()));
    timer->start(1000 / ldr.get_fps());

    look_at_r = glm::length(look_at_pos);

    ldr.get_scene("base").hello();
}

OpenGLWidget::~OpenGLWidget()
{
    timer->stop();
}

void OpenGLWidget::initializeGL() {
    glClearColor(1.0, 1.0, 1.0, 0.0);
    // 着色方式选择
    glShadeModel(GL_SMOOTH);
    // 深度测试
    glClearDepth(1.0);
    glEnable(GL_DEPTH_TEST);
    glColor3f(0, 0, 0);
}

void OpenGLWidget::resizeGL(int w, int h) {
    glViewport(0, 0, w, h);
    // GL_PROJECTION 投影, GL_MODELVIEW 模型视图, GL_TEXTURE 纹理.
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    // 视角的角度（眼睛睁开大小），窗口横纵比例，近处截面，远处截面
    gluPerspective(45.0, static_cast<double>(w) / h, 0.1, 100);
    double x = static_cast<double>(look_at_pos.x);
    double y = static_cast<double>(look_at_pos.y);
    double z = static_cast<double>(look_at_pos.z);
    double tx = static_cast<double>(target.x);
    double ty = static_cast<double>(target.y);
    double tz = static_cast<double>(target.z);
    double ux = static_cast<double>(up.x);
    double uy = static_cast<double>(up.y);
    double uz = static_cast<double>(up.z);
    gluLookAt(x, y, z, tx, ty, tz, ux, uy, uz);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    updateGL();
}

void OpenGLWidget::paintGL() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); // 清除缓冲区
    glLoadIdentity(); // 恢复初始坐标系

    glMatrixMode(GL_MODELVIEW); // 设置投影矩阵
    ldr.get_running_scene().draw();
}

void OpenGLWidget::timer_update()
{
    updateGL();
}
