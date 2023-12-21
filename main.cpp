#include "include/GraphVisualizer.h"

#include <QApplication>
#include <QMainWindow>
#include <QWidget>

// TODO MOVE LINE TO BACK

int main(int argc, char** argv)
{
    QApplication app(argc, argv);
    QMainWindow window;
    window.setFixedSize(800, 600);

    window.setCentralWidget(new GraphVisualizer(&window));

    window.show();

    return QApplication::exec();
}