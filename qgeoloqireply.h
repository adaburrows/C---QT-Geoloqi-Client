#ifndef GEOLOQIREPLY_H
#define GEOLOQIREPLY_H

#include <QObject>
#include <QString>
#include <QStringBuilder>
#include <QByteArray>
#include <QList>
#include <QStringList>
#include <QVector>
#include <QVectorIterator>
#include <QVariantMap>
#include <qjson/parser.h>
#include <qjson/serializer.h>
#include <QSslError>
#include <QNetworkRequest>
#include <QNetworkReply>
#include <QNetworkAccessManager>
#include <QTextStream>
#include <iostream>

class QGeoloqiReply : public QObject
{
    Q_OBJECT
public:
    QGeoloqiReply(QNetworkReply*);
public slots:
    void processReply();
signals:
    void finished(QVariant, QGeoloqiReply*);
    void error();
private:
    QNetworkReply* reply;
    QByteArray encodeJson(QVariant);
    QVariant decodeJson(QByteArray);
};

#endif // GEOLOQIREPLY_H
