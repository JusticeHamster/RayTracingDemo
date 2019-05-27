#ifndef OPENGLWIDGET_H
#define OPENGLWIDGET_H

#include <QWidget>
#include <QGLWidget>
#include <vector>

#include "tools/loader.hpp"

class OpenGLWidget : public QGLWidget {
    Q_OBJECT
public:
    explicit OpenGLWidget(QWidget *parent = nullptr);

protected:
    void initializeGL();
    void resizeGL(int w, int h);
    void paintGL();

private:
    loader &ldr = loader::instance;
};

#endif // OPENGLWIDGET_H
