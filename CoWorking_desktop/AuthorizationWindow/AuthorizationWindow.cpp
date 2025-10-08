#include "AuthorizationWindow/AuthorizationWindow.h"

#include <QHBoxLayout>
#include <QStackedWidget>
#include "AuthorizationWindow/LoginWigdet.h"
#include "AuthorizationWindow/SignupWidget.h"
#include "Network/NetworkManager.h"

AuthorizationWindow::AuthorizationWindow(NetworkManager* netManager, QWidget *parent)
    : QWidget{parent}, m_network(netManager)
{
    QHBoxLayout *mainLayout = new QHBoxLayout(this);
    m_stacked = new QStackedWidget();
    m_loginWidget = new LoginWidget(m_network);
    m_signupWidget = new SignupWidget(m_network);

    mainLayout->addWidget(m_stacked);
    m_stacked->addWidget(m_loginWidget);
    m_stacked->addWidget(m_signupWidget);
    m_stacked->setCurrentIndex(0);

    connect(m_loginWidget, &LoginWidget::signedIn, this, &AuthorizationWindow::loginSuccessful);
    connect(m_signupWidget, &SignupWidget::signedIn, this, &AuthorizationWindow::loginSuccessful);
}

void AuthorizationWindow::changeWidget(int index)
{
    m_stacked->setCurrentIndex(index);
}

