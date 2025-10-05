#ifndef SIGNUPWIDGET_H
#define SIGNUPWIDGET_H

#include <QWidget>

class QLineEdit;
class QPushButton;
class NetworkManager;

class SignupWidget : public QWidget
{
    Q_OBJECT
public:
    explicit SignupWidget(NetworkManager *networkManager, QWidget *parent = nullptr);

private:
    QLineEdit   *m_loginLine;
    QLineEdit   *m_nameLine;
    QLineEdit   *m_passwordLine;
    QLineEdit   *m_passwordRepeatLine;
    QPushButton *m_signupButton;

    NetworkManager *m_network;

private slots:
    void signupTry();

signals:
};

#endif // SIGNUPWIDGET_H
