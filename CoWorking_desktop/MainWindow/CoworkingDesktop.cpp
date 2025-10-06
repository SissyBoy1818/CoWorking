#include "CoworkingDesktop.h"

#include "MainWindow/MenuWidget.h"

#include <QVBoxLayout>

CoworkingDesktop::CoworkingDesktop(QWidget *parent)
    : QWidget{parent}
{
    auto *layout = new QVBoxLayout(this);

    m_menu = new MenuWidget(this);

    layout->addWidget(m_menu);
}
