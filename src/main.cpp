#include "Bootstrapper.hpp"
#include "util.hpp"

#include <QApplication>
#include <QMainWindow>

int main(int argc, char* argv[])
{
    QApplication app(argc, argv);

    QMainWindow gui;
    gui.setWindowTitle("lua-cxx");
    gui.resize(800, 600);

    Bootstrapper bootstrapper;
    gui.setCentralWidget(&bootstrapper.mainWidget());

    centerWindow(gui);

    return app.exec();
}

// vim: set ts=4 sw=4 :
