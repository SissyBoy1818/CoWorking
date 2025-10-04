#ifndef NETWORKMANAGER_H
#define NETWORKMANAGER_H

#include <QObject>

class QNetworkAccessManager;

class NetworkManager : public QObject
{
    Q_OBJECT
public:
    explicit NetworkManager(QObject *parent = nullptr);

    bool login(const QString &login, const QString &password);

private:
    QNetworkAccessManager *m_networkManager;
    QString serverAddr;

signals:
};

#endif // NETWORKMANAGER_H
