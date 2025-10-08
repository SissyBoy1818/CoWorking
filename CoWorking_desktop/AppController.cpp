#include "AppController.h"

#include "MainWindow/CoworkingDesktop.h"
#include "AuthorizationWindow/AuthorizationWindow.h"
#include "Network/NetworkManager.h"

#include <QApplication>

AppController::AppController(QObject *parent)
    : QObject{parent}, m_network(new NetworkManager)
{}

void AppController::start() {
    showLogin();
}

void AppController::showLogin() {
    if (m_loginWindow)
        return;
    if (m_mainWindow) {
        m_mainWindow->close();
        m_mainWindow = nullptr;
    }

    m_loginWindow = new AuthorizationWindow(m_network);
    m_loginWindow->show();

    QObject::connect(m_loginWindow, &AuthorizationWindow::loginSuccessful,
                     this, &AppController::showMainWindow);
}

void AppController::showMainWindow() {
    if (m_mainWindow)
        return;
    if (m_loginWindow) {
        m_loginWindow->close();
        m_loginWindow = nullptr;
    }

    m_mainWindow = new CoworkingDesktop(m_network);
    m_mainWindow->show();
}
