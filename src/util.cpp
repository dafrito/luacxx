#include "util.hpp"

#include <QMainWindow>
#include <QSize>
#include <QDesktopWidget>
#include <QApplication>
#include <QPoint>

void centerWindow(QMainWindow& window)
{
    QDesktopWidget* desktop = QApplication::desktop();

    int desktopArea = desktop->width() * desktop->height();
    int appArea = window.width() * window.height();
    if (((float)appArea / (float)desktopArea) > 0.75f) {
        // Just maximize it if the desktop isn't significantly
        // bigger than our app's area.
        window.showMaximized();
    } else {
        // Center the app on the primary monitor.
        QPoint windowLocation = desktop->screenGeometry(desktop->primaryScreen()).center();
        windowLocation.setX(windowLocation.x() - window.width() / 2);
        windowLocation.setY(windowLocation.y() - window.height() / 2);
        window.move(windowLocation);
        window.show();
    }
}

// vim: set ts=4 sw=4 :
