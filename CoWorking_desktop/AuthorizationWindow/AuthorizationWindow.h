#ifndef AUTHORIZATIONWINDOW_H
#define AUTHORIZATIONWINDOW_H

#include <QWidget>

class AuthorizationWindow : public QWidget
{
    Q_OBJECT
public:
    explicit AuthorizationWindow(QWidget *parent = nullptr);

signals:
};

#endif // AUTHORIZATIONWINDOW_H
