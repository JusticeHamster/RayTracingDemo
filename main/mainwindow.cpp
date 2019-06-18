#include "mainwindow.hpp"
#include "ui_mainwindow.h"

#include "tools/scene.hpp"
#include "tools/printer.hpp"

#include "object_list_model.hpp"
#include "object_list_delegate.hpp"

#include "glm/gtc/matrix_transform.hpp"

#include <QMouseEvent>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent)
{
    up = glm::vec3(0, 1, 0);
    left = glm::vec3(1, 0, 0);
    this->setWindowTitle("path tracing demo");
    init_widgets();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_start_clicked()
{
    r.render(ldr.get_scene("base"));
}

void MainWindow::mouseMoveEvent(QMouseEvent *event)
{
    if (last_pos.isNull()) {
        last_pos = event->pos();
        return;
    }
    auto gl = ui->openGL;
    QPoint diff = event->pos() - last_pos;
    float speed = ldr.get_factor("speed");
    int x = diff.x(), y = diff.y();
    glm::mat4 r(1.f);

    if (x != 0)
        r = r * glm::rotate(r, speed * x, up);

    if (y != 0)
        r = r * glm::rotate(r, -speed * y, left);

    up = glm::vec4(up, 0) * r;
    left = glm::vec4(left, 0) * r;
    gl->up = up;
    gl->look_at_pos = glm::vec4(gl->look_at_pos, 1) * r;

    auto size = gl->size();
    gl->resizeGL(size.width(), size.height());

    last_pos = event->pos();
}

void MainWindow::mouseReleaseEvent(QMouseEvent *event)
{
    last_pos = QPoint();
}

void MainWindow::resizeEvent(QResizeEvent *event)
{
    QMainWindow::resizeEvent(event);
    auto size = ui->openGL->size();
    ui->openGL->resizeGL(size.width(), size.height());
}

void MainWindow::init_widgets()
{
    ui = new Ui::MainWindow;
    ui->setupUi(this);
    model = new object_list_model(this);
    delegate = new object_list_delegate(model, this);
    ui->objectList->setModel(model);
    ui->objectList->setItemDelegate(delegate);
    ui->openGL->setMouseTracking(true);
    auto size = ui->openGL->size();
    ui->openGL->resizeGL(size.width(), size.height());
}
