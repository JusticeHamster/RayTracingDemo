#ifndef OPENGLWIDGET_H
#define OPENGLWIDGET_H

#include <QWidget>
#include <QGLWidget>

class OpenGLWidget : public QGLWidget {
    Q_OBJECT
public:
    explicit OpenGLWidget(QWidget *parent = nullptr);

protected:
    void initializeGL();
    void resizeGL(int w, int h);
    void paintGL();
};

#endif // OPENGLWIDGET_H
