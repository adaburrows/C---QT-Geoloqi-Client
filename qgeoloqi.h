#ifndef LOQICLIENT_H
#define LOQICLIENT_H

#include "qgeoloqireply.h"

class QGeoloqi : public QObject
{
    Q_OBJECT
public:
    QGeoloqi();
    QGeoloqi(QString, QString);

    QGeoloqiReply* getAuthToken(QString, QString);
    void setClientId(QString);
    void setClientSecret(QString);
    QString getToken();
    void setToken(QString);
    QGeoloqiReply* getUsername();
    QGeoloqiReply* getProfile();
    QGeoloqiReply* getLastLocation();
    QGeoloqiReply* getHistory();

    QByteArray encodeJson(QVariant);
    QVariant decodeJson(QByteArray);
    QByteArray encodeUrlEncoded(QVector<QPair<QString,QString> >&);
    QVector<QPair<QString,QString> > decodeUrlEncoded(QByteArray);
public slots:
    void sslErrors(QNetworkReply*, QList<QSslError>);
/*signals:
    void onError();
    void onUsername(QVariantMap);
    void onProfile(QVariantMap);
    void onLastLocation(QVariantMap);
    void onHistory(QVariantMap);*/
private:
    QNetworkAccessManager* manager;
    QString api_url;
    QString token;
    QString client_id;
    QString client_secret;
    void QGeoloqiCommon();
};

#endif // LOQICLIENT_H
