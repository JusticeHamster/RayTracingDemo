#ifndef OPENGLWIDGET_H
#define OPENGLWIDGET_H

#include <QWidget>
#include <QGLWidget>
#include <QtCore>
#include <memory>
#include <vector>

#include "tools/loader.hpp"

class OpenGLWidget : public QGLWidget {
    Q_OBJECT
public:
    explicit OpenGLWidget(QWidget *parent = nullptr);
    virtual ~OpenGLWidget();

protected:
    void initializeGL();
    void resizeGL(int w, int h);
    void paintGL();

private:
    loader &ldr;
    std::unique_ptr<QTimer> timer;

private slots:
    void timer_update();
};

#endif // OPENGLWIDGET_H
