#ifndef MENUWIDGET_H
#define MENUWIDGET_H

#include <QWidget>

class QPushButton;

class MenuWidget : public QWidget
{
    Q_OBJECT
public:
    explicit MenuWidget(QWidget *parent = nullptr);

private:
    QPushButton *m_workplacesButton;
    QPushButton *m_roomsButton;
    QPushButton *m_mybookingsButton;
    QPushButton *m_accountButton;

    void configurateButton(QPushButton *btn);

signals:
    void workplacesClicked();
    void roomsClicked();
    void bookingsClicked();
    void accountClicked();
};

#endif // MENUWIDGET_H
