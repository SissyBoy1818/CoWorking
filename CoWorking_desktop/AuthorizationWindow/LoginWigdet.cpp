#include "LoginWigdet.h"

#include <QPushButton>
#include <QLineEdit>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QLabel>
#include <QSpacerItem>

#include "Network/NetworkManager.h"

LoginWidget::LoginWidget(NetworkManager *netManager, QWidget *parent)
    : QWidget{parent}, m_network{netManager}
{

    QHBoxLayout *mainLayout = new QHBoxLayout(this);
    QVBoxLayout *authformLayout = new QVBoxLayout();

    QSpacerItem *spacer = new QSpacerItem(40,40, QSizePolicy::Expanding, QSizePolicy::Expanding);
    QSpacerItem *smallSpacer = new QSpacerItem(20,20);

    QLabel *loginLabel = new QLabel("Логин");
    QLabel *passwordLabel = new QLabel("Пароль");

    m_loginLine = new QLineEdit();
    m_passwordLine = new QLineEdit();

    m_signinButton = new QPushButton("Войти");

    mainLayout->addSpacerItem(spacer);
    mainLayout->addLayout(authformLayout);
    mainLayout->addSpacerItem(spacer);

    authformLayout->addSpacerItem(spacer);
    authformLayout->addWidget(loginLabel);
    authformLayout->addWidget(m_loginLine);
    authformLayout->addSpacerItem(smallSpacer);
    authformLayout->addWidget(passwordLabel);
    authformLayout->addWidget(m_passwordLine);
    authformLayout->addSpacerItem(smallSpacer);
    authformLayout->addWidget(m_signinButton);
    authformLayout->addSpacerItem(spacer);

    m_signinButton->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
    m_signinButton->setLayoutDirection(Qt::LayoutDirection::RightToLeft);

    m_loginLine->setMaxLength(32);
    m_passwordLine->setMaxLength(24);
    m_passwordLine->setEchoMode(QLineEdit::Password);

    connect(m_signinButton, &QPushButton::clicked, this, &LoginWidget::signinClicked);
    connect(m_network,&NetworkManager::successfulSignin, this, &LoginWidget::signedIn);

    setMinimumSize(750,500);
}

void LoginWidget::signinClicked()
{
    QString login = m_loginLine->text();
    QString password = m_passwordLine->text();
    m_network->signin(login, password);
}
