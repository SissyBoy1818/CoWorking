#ifndef COWORKINGDESKTOP_H
#define COWORKINGDESKTOP_H

#include <QWidget>

class MenuWidget;
class BookingsView;
class BookingDesktop;
class NetworkManager;

class CoworkingDesktop : public QWidget
{
    Q_OBJECT
public:
    explicit CoworkingDesktop(NetworkManager* netManager, QWidget *parent = nullptr);

private:
    MenuWidget   *m_menu;
    BookingsView *m_workpalceBookings;

    NetworkManager* m_network;

signals:
};

#endif // COWORKINGDESKTOP_H
