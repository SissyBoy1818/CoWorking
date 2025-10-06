#include "MenuWidget.h"

#include <QHBoxLayout>
#include <QSpacerItem>
#include <QPushButton>

MenuWidget::MenuWidget(QWidget *parent)
    : QWidget{parent}
{
    auto *mainLayout = new QHBoxLayout(this);
    auto *spacer = new QSpacerItem(40, 40, QSizePolicy::Expanding, QSizePolicy::Expanding);
    auto *smallSpacer = new QSpacerItem(20, 20);

    m_accountButton = new QPushButton("Мой\nаккаунт");
    m_mybookingsButton = new QPushButton("Мои\nброни");
    m_roomsButton = new QPushButton("Забронировать\nкомнату");
    m_workplacesButton = new QPushButton("Забронировать\nрабочее место");

    mainLayout->addSpacerItem(spacer);
    mainLayout->addWidget(m_workplacesButton);
    mainLayout->addWidget(m_roomsButton);
    mainLayout->addWidget(m_mybookingsButton);
    mainLayout->addSpacerItem(smallSpacer);
    mainLayout->addWidget(m_accountButton);
    mainLayout->addSpacerItem(spacer);

    configurateButton(m_accountButton);
    configurateButton(m_mybookingsButton);
    configurateButton(m_roomsButton);
    configurateButton(m_workplacesButton);
}

void MenuWidget::configurateButton(QPushButton *btn)
{
    btn->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    btn->setCheckable(true);
    btn->setAutoExclusive(true);
}
