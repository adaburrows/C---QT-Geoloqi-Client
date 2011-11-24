#include "qgeoloqireply.h"

/*
 * Contructors and related functions.
 * ============================================================================
 */

QGeoloqiReply::QGeoloqiReply(QNetworkReply* reply)
{
    this->reply = reply;
}

/*
 * Encoding and Decoding functions
 * ============================================================================
 */

QByteArray QGeoloqiReply::encodeJson(QVariant data) {
    QJson::Serializer serializer;
    return serializer.serialize(data);
}

QVariant QGeoloqiReply::decodeJson(QByteArray response) {
    QTextStream out(stdout);
    QJson::Parser parser;
    bool ok;
    QVariant result = parser.parse(response, &ok);
    if(!ok) {
        out << QString("Error parsing response: %1\n").arg(QString(response));
    }
    return result;
}

/*
 * Slots
 * ============================================================================
 */

void QGeoloqiReply::processReply() {
    QTextStream out(stdout);
    QVariant content;

    // Read in the response and check content
    QByteArray response = this->reply->readAll();
    //out << QString(response);
    QVariant contentType = this->reply->header(QNetworkRequest::ContentTypeHeader);
    if (contentType.isValid()) {
        QString cType = contentType.toString();
        if (cType == QString("application/json")) {
            content = decodeJson(response);
        } else {
            content = QVariant();
            out << QString("Got invalid Content-Type: %1\n").arg(QString(response));
            emit error();
        }
    }
    // If we've gotten valid content, process it and dispatch the signal
    if (content.isValid()) {
        // Each operation responds to a different signal
        switch (this->reply->operation()) {
            case QNetworkAccessManager::GetOperation:
            case QNetworkAccessManager::PutOperation:
            case QNetworkAccessManager::PostOperation:
            case QNetworkAccessManager::DeleteOperation:
            default:
                emit dataReady(content, this);
        }
    }
    this->reply->deleteLater();
    this->reply = NULL;
}
