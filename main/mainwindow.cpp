#include "mainwindow.hpp"
#include "ui_mainwindow.h"

#include "tools/scene.hpp"

#include "object_list_model.hpp"
#include "object_list_delegate.hpp"

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

void MainWindow::init_widgets()
{
    ui = new Ui::MainWindow;
    ui->setupUi(this);
    model = new object_list_model(this);
    delegate = new object_list_delegate(model, this);
    ui->objectList->setModel(model);
    ui->objectList->setItemDelegate(delegate);
}
