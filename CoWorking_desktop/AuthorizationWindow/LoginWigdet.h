#ifndef LOGINWIGDET_H
#define LOGINWIGDET_H

#include <QWidget>

class QLineEdit;
class QPushButton;
class NetworkManager;

class LoginWigdet : public QWidget
{
    Q_OBJECT
public:
    explicit LoginWigdet(NetworkManager *netManager,  QWidget *parent = nullptr);

private:
    NetworkManager  *m_network;

    QLineEdit   *m_loginLine;
    QLineEdit   *m_passwordLine;
    QPushButton *m_signinButton;

private slots:
    void signinClicked();

signals:
};

#endif // LOGINWIGDET_H
