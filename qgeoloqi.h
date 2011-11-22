#ifndef LOQICLIENT_H
#define LOQICLIENT_H

#include <QObject>
#include <QString>
#include <QStringBuilder>
#include <QByteArray>
#include <QList>
#include <QStringList>
#include <QVector>
#include <QVectorIterator>
#include <QVariantMap>
#include "qjson/parser.h"
#include "qjson/serializer.h"
#include <QSslError>
#include <QNetworkRequest>
#include <QNetworkReply>
#include <QNetworkAccessManager>
#include <QTextStream>
#include <iostream>

class QGeoloqi : public QObject
{
    Q_OBJECT
public:
    QGeoloqi();
    QGeoloqi(QString, QString);
    void getAuthToken(QString, QString);
    void setClientId(QString);
    void setClientSecret(QString);
    QString getToken();
    void setToken(QString);
    void getUsername();
    void getProfile();
    void getLastLocation();
    void getHistory();
    QNetworkReply* doRequest(QString);
    QByteArray encodeJson(QVariant);
    QVariant decodeJson(QByteArray);
    QByteArray encodeUrlEncoded(QVector<QPair<QString,QString> >&);
    QVector<QPair<QString,QString> > decodeUrlEncoded(QByteArray);
public slots:
    void processReply(QNetworkReply*);
    void sslErrors(QNetworkReply*, QList<QSslError>);
    void AuthTokenReady();
    void UsernameReady();
    void ProfileReady();
    void LastLocationReady();
    void HistoryReady();
signals:
    void onError();
    void onUsername(QVariantMap);
    void onProfile(QVariantMap);
    void onLastLocation(QVariantMap);
    void onHistory(QVariantMap);
private:
    QNetworkAccessManager* manager;
    QString api_url;
    QString token;
    QString client_id;
    QString client_secret;
    void QGeoloqiCommon();
};

#endif // LOQICLIENT_H
