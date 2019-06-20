#include "mainwindow.hpp"
#include "ui_mainwindow.h"

#include "tools/scene.hpp"
#include "tools/printer.hpp"
#include "tools/serializable.hpp"

#include "object_list_model.hpp"
#include "object_list_delegate.hpp"
#include "object_list_frame.hpp"

#include "glm/gtc/matrix_transform.hpp"

#include <QMouseEvent>
#include <QWheelEvent>
#include <QModelIndex>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent)
{
    up = glm::vec3(0, 1, 0);
    left = glm::vec3(1, 0, 0);
    init_widgets();
}

MainWindow::~MainWindow()
{
    delete ui;
    delete model;
    delete delegate;
}

void MainWindow::on_start_clicked()
{
    r.set_light_width_height({ui->rayRow->value(), ui->rayCol->value()});
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

    if (glm::abs(x) > glm::abs(y)) {
        r = r * glm::rotate(r, speed * x, up);
    } else {
        r = r * glm::rotate(r, -speed * y, left);
    }

    up = glm::vec4(up, 0) * r;
    left = glm::vec4(left, 0) * r;
    gl->up = up;
    gl->look_at_pos = glm::vec4(gl->look_at_pos, 1) * r;

    update_opengl();

    last_pos = event->pos();
}

void MainWindow::mouseReleaseEvent(QMouseEvent *event)
{
    last_pos = QPoint();
}

void MainWindow::wheelEvent(QWheelEvent *event)
{
    float delta_r = -ldr.get_factor("wheel_speed") * event->delta();
    auto gl = ui->openGL;
    if (gl->look_at_r + delta_r > 0)
        gl->look_at_r += delta_r;
    gl->look_at_pos = glm::normalize(gl->look_at_pos) * gl->look_at_r;

    update_opengl();
}

void MainWindow::resizeEvent(QResizeEvent *event)
{
    QMainWindow::resizeEvent(event);

    update_opengl();
}

void MainWindow::init_widgets()
{
    ui = new Ui::MainWindow;
    ui->setupUi(this);
    this->setWindowTitle("path tracing demo");
    model = new object_list_model(this);
    delegate = new object_list_delegate(model, this);
    model->parent = *this;
    model->serialize = &MainWindow::serialize;
    model->deserialize = &MainWindow::deserialize;
    model->load_data();
    ui->objectList->setModel(model);
    ui->objectList->setItemDelegate(delegate);
    ui->openGL->setMouseTracking(true);
    ui->openGL->model = model;

    update_opengl();
}

buffer MainWindow::serialize() const
{
    auto gl = ui->openGL;
    buffer b;

    buffer t = serializable::serialize(up);
    b.insert(b.end(), t.begin(), t.end());
    t = serializable::serialize(left);
    b.insert(b.end(), t.begin(), t.end());
    t = serializable::serialize(gl->look_at_pos);
    b.insert(b.end(), t.begin(), t.end());
    return b;
}

void MainWindow::deserialize(buffer &buf)
{
    auto gl = ui->openGL;

    serializable::deserialize(buf, gl->look_at_pos);
    serializable::deserialize(buf, left);
    serializable::deserialize(buf, up);
    gl->up = up;
    gl->look_at_r = glm::length(gl->look_at_pos);

    update_opengl();
}

void MainWindow::update_opengl()
{
    auto gl = ui->openGL;

    auto size = gl->size();
#ifdef __APPLE__
    // macos retina
    size = size * 2;
#endif
    gl->resizeGL(size.width(), size.height());
}

void MainWindow::set_selected()
{
    auto in = ui->objectList->currentIndex();
    scene &scn = ldr.get_running_scene();
    if (scn.object_count() <= in.row())
        return;
    model->set_selected(scn.get_model(in.row()));
}

void MainWindow::on_save_button_clicked()
{
    model->save_data();
}

void MainWindow::on_load_button_clicked()
{
    model->load_data();
}

void MainWindow::on_rotate_clicked()
{
    set_selected();
    model->rotate(static_cast<float>(ui->rotateAngle->value()));
}

void MainWindow::on_deleteButton_clicked()
{
    set_selected();
    model->remove_selected();
    set_selected();
}
