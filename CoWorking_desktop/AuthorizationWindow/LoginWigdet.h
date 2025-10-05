#ifndef LOGINWIGDET_H
#define LOGINWIGDET_H

#include <QWidget>

class QLineEdit;
class QPushButton;
class NetworkManager;

class LoginWidget : public QWidget
{
    Q_OBJECT
public:
    explicit LoginWidget(NetworkManager *netManager,  QWidget *parent = nullptr);

private:
    NetworkManager  *m_network;

    QLineEdit   *m_loginLine;
    QLineEdit   *m_passwordLine;
    QPushButton *m_signinButton;

private slots:
    void signinClicked();

signals:
    void signedIn(int);
};

#endif // LOGINWIGDET_H
