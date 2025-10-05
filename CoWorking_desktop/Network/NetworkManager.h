#ifndef NETWORKMANAGER_H
#define NETWORKMANAGER_H

#include <QObject>

class QNetworkAccessManager;

class NetworkManager : public QObject
{
    Q_OBJECT
public:
    explicit NetworkManager(QObject *parent = nullptr);

    void signin(const QString &login, const QString &password);
    void signup(const QString &name, const QString &login, const QString &password);
    void getWorkplaces();

private:
    QNetworkAccessManager *m_networkManager;
    QString m_serverAddr;
    QString m_token;

signals:
    void successfulSignin();
    void successfulSignup();
};

#endif // NETWORKMANAGER_H
