#include "qgeoloqi.h"



/*
 * Contructors and related functions.
 * ============================================================================
 */

QGeoloqi::QGeoloqi()
{
    QGeoloqiCommon();
}

QGeoloqi::QGeoloqi(QString client_id, QString client_secret) {
    QGeoloqiCommon();
    this->client_id = client_id;
    this->client_secret = client_secret;
}

// Common setup in the above constructors
void QGeoloqi::QGeoloqiCommon()
{
    this->api_url = QString("https://api.geoloqi.com/1/");
    this->client_id = QString("");
    this->client_secret = QString("");
    this->manager = new QNetworkAccessManager();
    connect(this->manager, SIGNAL(finished(QNetworkReply*)), this, SLOT(processReply(QNetworkReply*)));
    connect(this->manager, SIGNAL(sslErrors(QNetworkReply*,QList<QSslError>)), this, SLOT(sslErrors(QNetworkReply*, QList<QSslError>)));
}

/*
 * API Methods
 * ============================================================================
 */

// Set the Client ID -- value given at application registration
void QGeoloqi::setClientId(QString client_id) {
    this->client_id = client_id;
}

// Set the Client Secret -- value given at application registration
void QGeoloqi::setClientSecret(QString client_secret) {
    this->client_secret = client_secret;
}

// Get the auth token using geoloqi username and password
void QGeoloqi::getAuthToken(QString user, QString pass) {
    // Set up the parameters fo be sen URL Encoded
    QVector<QPair<QString,QString> > payloadData;
    payloadData.push_back(QPair<QString,QString>(QString("grant_type"), QString("password")));
    payloadData.push_back(QPair<QString,QString>(QString("username"), user));
    payloadData.push_back(QPair<QString,QString>(QString("password"), pass));
    payloadData.push_back(QPair<QString,QString>(QString("client_id"), this->client_id));
    payloadData.push_back(QPair<QString,QString>(QString("client_secret"), this->client_secret));
    QByteArray payload = encodeUrlEncoded(payloadData);

    QUrl url = QUrl(this->api_url % QString("oauth/token"));
    QNetworkRequest request = QNetworkRequest(url);
    QNetworkReply* reply = manager->post(request,payload);

    connect(reply, SIGNAL(finished()), this, SLOT(AuthTokenReady()));
}

QString QGeoloqi::getToken() {
    return this->token;
}

void QGeoloqi::setToken(QString token) {
    this->token = token;
}

void QGeoloqi::getUsername() {
    QUrl url = QUrl(this->api_url % QString("account/username"));
    url.addQueryItem(QString("oauth_token"), this->token);
    QNetworkRequest request = QNetworkRequest(url);
    QNetworkReply* reply = manager->get(request);

    connect(reply, SIGNAL(finished()), this, SLOT(UsernameReady()));
}

void QGeoloqi::getProfile() {
    QUrl url = QUrl(this->api_url % QString("account/profile"));
    url.addQueryItem(QString("oauth_token"), this->token);
    QNetworkRequest request = QNetworkRequest(url);
    QNetworkReply* reply = manager->get(request);

    connect(reply, SIGNAL(finished()), this, SLOT(ProfileReady()));
}

void QGeoloqi::getLastLocation() {
    QUrl url = QUrl(this->api_url % QString("location/last"));
    url.addQueryItem(QString("oauth_token"), this->token);
    QNetworkRequest request = QNetworkRequest(url);
    QNetworkReply* reply = manager->get(request);

    connect(reply, SIGNAL(finished()), this, SLOT(LastLocationReady()));
}

void QGeoloqi::getHistory() {
    QUrl url = QUrl(this->api_url % QString("location/history"));
    url.addQueryItem(QString("oauth_token"), this->token);
    QNetworkRequest request = QNetworkRequest(url);
    QNetworkReply* reply = manager->get(request);

    connect(reply, SIGNAL(finished()), this, SLOT(HistoryReady()));
}


/*
 * Encoding and Decoding functions
 * ============================================================================
 */

QByteArray QGeoloqi::encodeJson(QVariant data) {
    QJson::Serializer serializer;
    return serializer.serialize(data);
}

QVariant QGeoloqi::decodeJson(QByteArray response) {
    QTextStream out(stdout);
    QJson::Parser parser;
    bool ok;
    QVariant result = parser.parse(response, &ok);
    if(!ok) {
        out << QString("Error parsing response: %1\n").arg(QString(response));
    }
    return result;
}

QByteArray QGeoloqi::encodeUrlEncoded(QVector<QPair<QString,QString> >& dataMap) {
    QTextStream out(stdout);
    QString encoded = QString("");
    QVectorIterator<QPair<QString,QString> > i(dataMap);
    QStringList parts = QStringList();
    while (i.hasNext()) {
        QPair<QString,QString> value = i.next();
        //out << QString("%1 : %2\n").arg(value.first).arg(value.second);
        parts.append(value.first % QString("=") % value.second);
    }
    encoded = parts.join("&");
    return encoded.toAscii();
}

QVector<QPair<QString,QString> > QGeoloqi::decodeUrlEncoded(QByteArray data) {
    QVector<QPair<QString, QString> > items;
    QStringList parts = QString(data).split("&");
    QStringListIterator i(parts);
    while(i.hasNext()) {
        QStringList item = i.next().split("=");
        items.push_back(QPair<QString,QString>(item.at(0),item.at(1)));
    }
    return items;
}

/*
 * Slots
 * ============================================================================
 */

void QGeoloqi::processReply(QNetworkReply* reply) {
    QTextStream out(stdout);
    QVariant content;

    // Get the original request to see what request type this reply is for
    QNetworkRequest request = reply->request();

    // Read in the response and check content
    QByteArray response = reply->readAll();
    out << QString(response);
    QVariant contentType = reply->header(QNetworkRequest::ContentTypeHeader);
    if (contentType.isValid()) {
        QString cType = contentType.toString();
        if (cType == QString("application/json")) {
            content = decodeJson(response);
        } else {
            content = QVariant();
            out << QString("Got invalid Content-Type: %1\n").arg(QString(response));
            emit onError();
        }
    }
    // If we've gotten valid content, process it and dispatch the signal
    if (content.isValid()) {
        QVariantMap data = content.toMap();
        // Each operation responds to a different signal
        switch (reply->operation()) {
            case QNetworkAccessManager::GetOperation:
            case QNetworkAccessManager::PutOperation:
            case QNetworkAccessManager::PostOperation:
            case QNetworkAccessManager::DeleteOperation:
            default:
              out << data["username"].toString() << "\n";
        }
    }
    reply->deleteLater();
}

void QGeoloqi::sslErrors(QNetworkReply * reply, QList<QSslError> errors) {
    QTextStream out(stdout);
    out << reply->readAll();
    QListIterator<QSslError> errorIterator(errors);

    while (errorIterator.hasNext()) {
        out << QString("SSL Error: %1\n").arg(errorIterator.next().errorString());
    }
    out << QString("%1 SSL Errors.\n").arg(errors.length());
}

void QGeoloqi::AuthTokenReady() {
    QTextStream out(stdout);
    out << "AuthToken Ready.\n";
}

void QGeoloqi::UsernameReady() {
    QTextStream out(stdout);
    out << "Username Ready.\n";
}

void QGeoloqi::ProfileReady() {
    QTextStream out(stdout);
    out << "Profile Ready.\n";
}

void QGeoloqi::LastLocationReady() {
    QTextStream out(stdout);
    out << "Last Location Ready.\n";
}

void QGeoloqi::HistoryReady() {
    QTextStream out(stdout);
    out << "History Ready.\n";
}
