#include "CoworkingDesktop.h"

#include "MainWindow/BookingsView.h"
#include "MainWindow/MenuWidget.h"

#include <QVBoxLayout>

CoworkingDesktop::CoworkingDesktop(NetworkManager *netManager, QWidget *parent)
    : QWidget{parent}, m_network{netManager}
{
    auto *layout = new QVBoxLayout(this);

    m_menu = new MenuWidget(this);
    m_workpalceBookings = new BookingsView(netManager, this);

    layout->addWidget(m_workpalceBookings);
    layout->addWidget(m_menu);

    m_menu->setFixedHeight(70);
}
