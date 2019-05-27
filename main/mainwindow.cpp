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
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_start_clicked()
{
    scene scn = ldr.get_scene("base");
    r.render(scn);
}
