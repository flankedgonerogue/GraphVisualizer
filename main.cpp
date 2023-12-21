#include <QApplication>
#include <iostream>
#include "include/Graph.h"
#include "ui_main-window.h"

int main(int argc, char** argv)
{
    QApplication app(argc, argv);
    QMainWindow main_window(nullptr);
    Ui::MainWindow window;
    window.setupUi(&main_window);

    main_window.show();

    return QApplication::exec();
}