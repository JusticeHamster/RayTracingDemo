#ifndef OPENGLWIDGET_H
#define OPENGLWIDGET_H

#include <QWidget>
#include <QGLWidget>
#include <QTimer>
#include <vector>

#include "shader.hpp"

class OpenGLWidget : public QGLWidget {
    Q_OBJECT
public:
    explicit OpenGLWidget(QWidget *parent = nullptr);
    int R;
    float x,y,z;

    void buttonclick();

protected:
    void initializeGL();
    void resizeGL(int w, int h);
    void paintGL();
    std::vector<shader> shaders;

private:
    // 绘制球体
    void drawSphere(GLfloat xx = 0.0,
                    GLfloat yy = 0.0,
                    GLfloat zz = 0.0,
                    GLfloat radius = 1.0,
                    GLfloat M = 100.0,
                    GLfloat N = 100.0);
    void drawTetrahedron();
    void drawCube();
    QTimer timer;
};

#endif // OPENGLWIDGET_H
