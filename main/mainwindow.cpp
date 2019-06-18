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
    glm::vec3 v = {diff.x(), diff.y(), 0};
    float angle = 2 * ldr.get_factor("speed") * glm::asin(v.length() / (2 * gl->look_at_r));
    v = glm::normalize(glm::cross(-gl->look_at_pos, v));
    glm::mat4 r(1.f);
    qDebug() << angle;
    printer::print(printer::format(v));
    gl->look_at_pos = glm::vec4(gl->look_at_pos, 1) * glm::rotate(r, angle, v);

    auto size = ui->openGL->size();
    ui->openGL->resizeGL(size.width(), size.height());

    last_pos = event->pos();
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
