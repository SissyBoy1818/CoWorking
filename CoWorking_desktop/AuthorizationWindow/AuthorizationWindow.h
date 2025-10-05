#ifndef AUTHORIZATIONWINDOW_H
#define AUTHORIZATIONWINDOW_H

#include <QWidget>

class QStackedWidget;
class LoginWidget;
class SignupWidget;
class NetworkManager;

class AuthorizationWindow : public QWidget
{
    Q_OBJECT
public:
    explicit AuthorizationWindow(QWidget *parent = nullptr);

private:
    QStackedWidget  *m_stacked;
    LoginWidget     *m_loginWidget;
    SignupWidget    *m_signupWidget;

    NetworkManager  *m_network;

private slots:
    void changeWidget(int index);

signals:
};

#endif // AUTHORIZATIONWINDOW_H
