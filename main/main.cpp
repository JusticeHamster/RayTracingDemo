#include "mainwindow.hpp"
#include "tester.hpp"

#include <QApplication>
#include <cstring>

int main(int argc, char *argv[])
{
    if (argc > 1 && strcmp(argv[1], "test") == 0) {
        tester t;
        t.test_all();
        return 0;
    } else {
        QApplication a(argc, argv);
        MainWindow w;
        w.show();

        return a.exec();
    }
}
