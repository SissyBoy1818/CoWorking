#ifndef BOOKINGSVIEW_H
#define BOOKINGSVIEW_H

#include <QWidget>
#include "MainWindow/BookingItem.h"

class QListWidget;

class BookingsView : public QWidget
{
    Q_OBJECT
public:
    explicit BookingsView(QWidget *parent = nullptr);

private:
    QListWidget *m_view;
    QList<BookingItem*> m_items;

signals:
};

#endif // BOOKINGSVIEW_H
