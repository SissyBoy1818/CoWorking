#include "BookingsView.h"

#include "MainWindow/AcceptBookingWindow.h"
#include "MainWindow/BookingItem.h"
#include "Network/NetworkManager.h"

#include <QPropertyAnimation>
#include <QListWidget>
#include <QPushButton>
#include <QVBoxLayout>
#include <QLabel>

BookingsView::BookingsView(NetworkManager *netManager, QWidget *parent)
    : QWidget{parent}, m_network(netManager)
{
    auto *l = new QVBoxLayout(this);
    m_view = new QListWidget();

    m_view->setViewMode(QListView::IconMode);
    m_view->setResizeMode(QListView::Adjust);
    m_view->setMovement(QListView::Static);
    m_view->setSpacing(30);

    for (int var = 0; var < 10; ++var) {
        auto item = new QListWidgetItem(QString("%1:00").arg(var, 2, 10, QChar('0')));
        item->setSizeHint(QSize(350, 150));
        m_view->addItem(item);
        m_items.append(std::move(item));
        m_view->setItemWidget(item, new BookingItem(this));
        m_view->itemWidget(item)->setEnabled(false);
    }

    connect(m_view, &QListWidget::currentItemChanged, this, &BookingsView::itemChanged);

    setLayout(l);
    l->addWidget(m_view);
    setMinimumSize(900,500);

    m_bookButton = new QPushButton("Book", this);
    m_bookButton->move(this->width()-120, this->height()-50);
    connect(m_bookButton, &QPushButton::clicked, this, &BookingsView::book);
}

void BookingsView::updateItems()
{
    m_network->getWorkplaces();

    for (auto *item : m_items) {
        BookingItem *widget = qobject_cast<BookingItem*>(m_view->itemWidget(item));

        widget->updateHours({});
    }
}

void BookingsView::resizeEvent(QResizeEvent *event)
{
    m_bookButton->move(this->width()-120, this->height()-50);
    QWidget::resizeEvent(event);
}

void BookingsView::book()
{
    auto *curItem = m_view->currentItem();
    if (!curItem)
        return;

    BookingItem *widget = qobject_cast<BookingItem*>(m_view->itemWidget(curItem));

    auto *dialog = new AcceptBookingWindow(widget->name(), "22.04.2025", widget->hours().size());

    if (dialog->exec() == QDialog::Accepted)
        qDebug() << "Пользователь нажал OK";
}

void BookingsView::itemChanged(QListWidgetItem *current, QListWidgetItem *previous)
{
    m_view->itemWidget(current)->setEnabled(true);

    if (previous)
        m_view->itemWidget(previous)->setEnabled(false);
}
