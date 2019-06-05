#include "mainwindow.hpp"
#include "ui_mainwindow.h"

#include "tools/scene.hpp"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
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
