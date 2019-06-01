#include "mainwindow.hpp"
#include "ui_mainwindow.h"

#include "tools/pinhole_camera.hpp"
#include "tools/scene.hpp"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow),
    r(pinhole_camera())
{
    ui->setupUi(this);
    start_button = findChild<QPushButton *>("start");
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_start_clicked()
{
    r.render(ldr.get_scene("base"));
}
