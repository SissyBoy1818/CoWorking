#include "AppController.h"
#include "MainWindow/BookingsView.h"
#include "MainWindow/CoworkingDesktop.h"
#include "MainWindow/AcceptBookingWindow.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    // AppController controller;
    // controller.start();
    CoworkingDesktop v(nullptr);
    //AcceptBookingWindow a("3-401", "22.04.2025", 8);
    //BookingItem i;
    //BookingsView w(nullptr);
    v.show();
    //a.show();
    //i.show();
    //w.show();

    return app.exec();
}
