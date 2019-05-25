#include "mainwindow.hpp"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButton_clicked()
{
    ui->openGLWidget->x += 1;
    ui->openGLWidget->y += 1;
    ui->openGLWidget->z += 1;
    ui->openGLWidget->buttonclick();
}
