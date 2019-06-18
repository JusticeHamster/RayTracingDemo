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
    float look_at_r;
    glm::vec3 look_at_pos = {-3, 2, -10};

    explicit OpenGLWidget(QWidget *parent = nullptr);
    virtual ~OpenGLWidget();

    void resizeGL(int w, int h);

protected:
    void initializeGL();
    void paintGL();

private:
    loader &ldr;
    std::unique_ptr<QTimer> timer;

private slots:
    void timer_update();
};

#endif // OPENGLWIDGET_H
