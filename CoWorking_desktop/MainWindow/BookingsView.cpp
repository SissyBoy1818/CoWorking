#include "BookingsView.h"

#include <QListWidget>
#include <QPushButton>
#include <QVBoxLayout>

BookingsView::BookingsView(QWidget *parent)
    : QWidget{parent}
{
    auto *l = new QVBoxLayout(this);
    m_view = new QListWidget();

    m_view->setViewMode(QListView::IconMode);
    m_view->setResizeMode(QListView::Adjust);
    m_view->setMovement(QListView::Static);

    for (int var = 0; var < 10; ++var) {
        auto item = new BookingItem();
        item->setSizeHint(QSize(170, 170));
        m_view->addItem(item);
        m_items.append(std::move(item));
    }
    m_view->setItemWidget(m_items.at(0), new QPushButton("Press"));

    setLayout(l);
    l->addWidget(m_view);
    setMinimumSize(500,500);
}
