#include "SignupWidget.h"

#include "Network/NetworkManager.h"

#include <QRegularExpressionValidator>
#include <QSpacerItem>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QPushButton>
#include <QLineEdit>
#include <QLabel>

SignupWidget::SignupWidget(NetworkManager *networkManager, QWidget *parent)
    : QWidget{parent}, m_network{networkManager}
{
    auto *mainLayout = new QHBoxLayout(this);
    auto *regFormLayout = new QVBoxLayout();

    auto *spacer = new QSpacerItem(40, 40, QSizePolicy::Expanding, QSizePolicy::Expanding);
    auto *smallSpacer = new QSpacerItem(20, 20, QSizePolicy::Minimum, QSizePolicy::Minimum);

    m_nameLine = new QLineEdit();
    m_loginLine = new QLineEdit();
    m_passwordLine = new QLineEdit();
    m_passwordRepeatLine = new QLineEdit();

    auto *nameLabel = new QLabel("Имя");
    auto *loginLabel = new QLabel("Логин");
    auto *passwordLabel = new QLabel("Пароль");
    auto *passwordRepeatLabel = new QLabel("Повторите пароль");

    m_signupButton = new QPushButton("Зарегистрироваться");

    mainLayout->addSpacerItem(spacer);
    mainLayout->addLayout(regFormLayout);
    mainLayout->addSpacerItem(spacer);

    regFormLayout->addSpacerItem(spacer);
    regFormLayout->addWidget(nameLabel);
    regFormLayout->addWidget(m_nameLine);
    regFormLayout->addSpacerItem(smallSpacer);
    regFormLayout->addWidget(loginLabel);
    regFormLayout->addWidget(m_loginLine);
    regFormLayout->addSpacerItem(smallSpacer);
    regFormLayout->addWidget(passwordLabel);
    regFormLayout->addWidget(m_passwordLine);
    regFormLayout->addSpacerItem(smallSpacer);
    regFormLayout->addWidget(passwordRepeatLabel);
    regFormLayout->addWidget(m_passwordRepeatLine);
    regFormLayout->addSpacerItem(smallSpacer);
    regFormLayout->addWidget(m_signupButton);
    regFormLayout->addSpacerItem(spacer);

    m_nameLine->setMaxLength(32);
    m_loginLine->setMaxLength(32);
    m_passwordLine->setMaxLength(24);
    m_passwordRepeatLine->setMaxLength(24);

    m_passwordLine->setEchoMode(QLineEdit::Password);
    m_passwordRepeatLine->setEchoMode(QLineEdit::Password);

    m_signupButton->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
    m_signupButton->setLayoutDirection(Qt::LayoutDirection::RightToLeft);

    connect(m_signupButton, &QPushButton::clicked, this, &SignupWidget::signupTry);
}

void SignupWidget::signupTry()
{
    QRegularExpression rx(R"(^((?:[a-zA-Z0-9!#$%&'*+/=?^_`{|}~-]+(?:\.[a-zA-Z0-9!#$%&'*+/=?^_`{|}~-]+)*)@((?:[a-zA-Z0-9](?:[a-zA-Z0-9-]{0,61}[a-zA-Z0-9])?\.)+[a-zA-Z]{2,}))$)");
    QRegularExpressionValidator validator(rx);
    int pos = 0;

    auto name = m_nameLine->text();
    auto login = m_loginLine->text();
    auto password = m_passwordLine->text();
    auto passwordRepeat = m_passwordRepeatLine->text();

    auto state = validator.validate(login, pos);

    if (state != QValidator::Acceptable)
        return;
    if (password != passwordRepeat)
        return;

    m_network->signup(name, login, password);
}
