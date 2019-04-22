#ifndef OPENGLWIDGET_H
#define OPENGLWIDGET_H

#include <QWidget>
#include <QGLWidget>

#include <vector>

#include "shader.hpp"

class OpenGLWidget : public QGLWidget {
    Q_OBJECT
public:
    explicit OpenGLWidget(QWidget *parent = nullptr);

protected:
    void initializeGL();
    void resizeGL(int w, int h);
    void paintGL();
    std::vector<shader> shaders;
};

#endif // OPENGLWIDGET_H
