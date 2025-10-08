#ifndef APPCONTROLLER_H
#define APPCONTROLLER_H

#include <QObject>

class AuthorizationWindow;
class CoworkingDesktop;
class NetworkManager;

class AppController : public QObject
{
    Q_OBJECT
public:
    explicit AppController(QObject *parent = nullptr);

    void start();

private:
    NetworkManager *m_network;

    AuthorizationWindow *m_loginWindow;
    CoworkingDesktop    *m_mainWindow;

    void showLogin();
    void showMainWindow();
};

#endif // APPCONTROLLER_H
