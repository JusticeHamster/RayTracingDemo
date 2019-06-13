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

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_start_clicked();

private:
    void init_widgets();

    Ui::MainWindow *ui;
    renderer r;
    loader &ldr = loader::instance;

    object_list_model *model;
    object_list_delegate *delegate;
};

#endif // MAINWINDOW_H
