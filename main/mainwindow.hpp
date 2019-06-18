#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QPushButton>

#include "renderer.hpp"
#include "tools/loader.hpp"

namespace Ui {
class MainWindow;
}

class object_list_model;
class object_list_delegate;

class MainWindow : public QMainWindow
{
    Q_OBJECT

private slots:
    void on_start_clicked();

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

protected:
    void mouseMoveEvent(QMouseEvent *event);
    void mouseReleaseEvent(QMouseEvent *event);
    void resizeEvent(QResizeEvent* event);

private:
    glm::vec3 up, left;
    QPoint last_pos;

    void init_widgets();

    Ui::MainWindow *ui;
    renderer r;
    loader &ldr = loader::instance;

    object_list_model *model;
    object_list_delegate *delegate;
};

#endif // MAINWINDOW_H
