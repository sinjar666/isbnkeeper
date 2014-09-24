
#include <QtGui/QApplication>
#include "stillcam.h"
#include "Homescreen/homescreen.h"


int main(int argc, char *argv[])
{
    g_digicam_init(&argc,&argv);
    QApplication app(argc, argv);
    app.setAttribute(Qt::AA_NativeWindows);
    app.setApplicationVersion(QString("1.0.1"));
    app.setApplicationName(QString("ISBN Keeper"));
    app.setOrganizationName(QString("Code Demons"));
    HomeScreen w;
    w.setAttribute(Qt::WA_Maemo5LandscapeOrientation);
    w.setAttribute(Qt::WA_Maemo5StackedWindow);
    w.show();

    return app.exec();
}
