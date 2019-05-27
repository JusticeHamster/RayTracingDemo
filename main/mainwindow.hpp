#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

#include "renderer.hpp"
#include "tools/loader.hpp"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_start_clicked();

private:
    Ui::MainWindow *ui;
    renderer r;
    loader &ldr = loader::instance;
};

#endif // MAINWINDOW_H
