#include "NetworkManager.h"

#include <QNetworkAccessManager>
#include <QNetworkRequest>
#include <QNetworkReply>
#include <QUrlQuery>

NetworkManager::NetworkManager(QObject *parent)
    : QObject{parent}
{
    m_networkManager = new QNetworkAccessManager(this);
    serverAddr = "http://127.0.0.1:8000";
}

bool NetworkManager::login(const QString &login, const QString &password)
{
    QNetworkRequest request(serverAddr + "/token");
    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/x-www-form-urlencoded; charset=utf-8");

    QByteArray data;
    data.append("grant_type=password&");
    data.append("username=" + QUrl::toPercentEncoding(login) + "&");
    data.append("password=" + QUrl::toPercentEncoding(password) + "&");
    data.append("scope=&client_id=&client_secret=");

    QNetworkReply *reply = m_networkManager->post(request, data);

    connect(reply, &QNetworkReply::finished, this, [reply]() {
        if (reply->error() == QNetworkReply::NoError) {
            QByteArray response_data = reply->readAll();
            qDebug() << "Ответ от сервера:" << response_data;
        } else {
            qDebug() << "Ошибка:" << reply->errorString();
        }
        reply->deleteLater();
    });

    return true;
}
