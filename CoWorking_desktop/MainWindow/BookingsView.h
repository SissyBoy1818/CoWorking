#ifndef BOOKINGSVIEW_H
#define BOOKINGSVIEW_H

#include <QWidget>
#include <QListWidgetItem>

class QListWidget;
class QPushButton;
class NetworkManager;

class BookingsView : public QWidget
{
    Q_OBJECT
public:
    explicit BookingsView(NetworkManager *netManager, QWidget *parent = nullptr);

private:
    NetworkManager *m_network;

    QListWidget *m_view;
    QList<QListWidgetItem*> m_items;

    QPushButton *m_bookButton;

    void updateItems();
    void resizeEvent(QResizeEvent *event) override;

private slots:
    void book();
    void itemChanged(QListWidgetItem *current, QListWidgetItem *previous);

signals:
};

#endif // BOOKINGSVIEW_H
