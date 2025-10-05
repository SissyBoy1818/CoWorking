#include "NetworkManager.h"

#include <QNetworkAccessManager>
#include <QNetworkRequest>
#include <QNetworkReply>
#include <QUrlQuery>
#include <QJsonObject>

NetworkManager::NetworkManager(QObject *parent)
    : QObject{parent}
{
    m_networkManager = new QNetworkAccessManager(this);
    m_serverAddr = "http://127.0.0.1:8000";
}

void NetworkManager::signin(const QString &login, const QString &password)
{
    QNetworkRequest request(m_serverAddr + "/token");
    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/x-www-form-urlencoded; charset=utf-8");

    QByteArray data;
    data.append("grant_type=password&");
    data.append("username=" + QUrl::toPercentEncoding(login) + "&");
    data.append("password=" + QUrl::toPercentEncoding(password) + "&");
    data.append("scope=&client_id=&client_secret=");

    QNetworkReply *reply = m_networkManager->post(request, data);

    connect(reply, &QNetworkReply::finished, this, [reply, this]() {
        if (reply->error() == QNetworkReply::NoError) {
            auto response_data = reply->readAll();
            QJsonDocument doc = QJsonDocument::fromJson(response_data);
            QJsonObject obj = doc.object();
            m_token = obj["access_token"].toString();

            qDebug() << m_token;
            if (!m_token.isEmpty())
                emit successfulSignin();
        } else {
            qDebug() << "Ошибка:" << reply->errorString();
        }
        reply->deleteLater();
    });
}

void NetworkManager::signup(const QString &name, const QString &login, const QString &password)
{
    QNetworkRequest request(m_serverAddr + "/signup?name=" + name);
    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/x-www-form-urlencoded; charset=utf-8");

    QByteArray data;
    data.append("grant_type=password&");
    data.append("username=" + QUrl::toPercentEncoding(login) + "&");
    data.append("password=" + QUrl::toPercentEncoding(password) + "&");
    data.append("scope=&client_id=&client_secret=");

    QNetworkReply *reply = m_networkManager->post(request, data);

    connect(reply, &QNetworkReply::finished, this, [reply, this]() {
        if (reply->error() == QNetworkReply::NoError) {
            auto response_data = reply->readAll();
            QJsonDocument doc = QJsonDocument::fromJson(response_data);
            QJsonObject obj = doc.object();
            m_token = obj["access_token"].toString();

            qDebug() << m_token;
            if (!m_token.isEmpty())
                emit successfulSignin();
        } else {
            qDebug() << "Ошибка:" << reply->errorString();
        }
        reply->deleteLater();
    });
}

void NetworkManager::getWorkplaces()
{
    QNetworkRequest request(m_serverAddr + "/workplaces");
    QString authHeader = "Bearer " + m_token;
    request.setRawHeader("Authorization", authHeader.toUtf8());

    QNetworkReply *reply = m_networkManager->get(request);

    connect(reply, &QNetworkReply::finished, this, [reply]() {
        if (reply->error() == QNetworkReply::NoError) {
            auto response_data = reply->readAll();
            qDebug() << response_data;
        } else {
            qDebug() << "Ошибка:" << reply->errorString();
        }
        reply->deleteLater();
    });
}
