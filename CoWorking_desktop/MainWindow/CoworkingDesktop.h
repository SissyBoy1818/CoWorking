#ifndef COWORKINGDESKTOP_H
#define COWORKINGDESKTOP_H

#include <QWidget>

class MenuWidget;
class BookingDesktop;

class CoworkingDesktop : public QWidget
{
    Q_OBJECT
public:
    explicit CoworkingDesktop(QWidget *parent = nullptr);

private:
    MenuWidget *m_menu;

signals:
};

#endif // COWORKINGDESKTOP_H
