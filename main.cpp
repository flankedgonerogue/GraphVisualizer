#include "ui_main-window.h"

int main(int argc, char** argv)
{
    QApplication app(argc, argv);
    QMainWindow main_window;
    Ui::MainWindow base;
    base.setupUi(&main_window);

    main_window.show();

    return QApplication::exec();
}
