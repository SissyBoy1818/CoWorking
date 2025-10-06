#ifndef APPCONTROLLER_H
#define APPCONTROLLER_H

#include <QObject>

class AuthorizationWindow;
class CoworkingDesktop;

class AppController : public QObject
{
    Q_OBJECT
public:
    explicit AppController(QObject *parent = nullptr);

    void start();

private:
    AuthorizationWindow *m_loginWindow = nullptr;
    CoworkingDesktop    *m_mainWindow  = nullptr;

    void showLogin();
    void showMainWindow();
};

#endif // APPCONTROLLER_H
