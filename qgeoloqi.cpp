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
    connect(this->manager, SIGNAL(sslErrors(QNetworkReply*,QList<QSslError>)), this, SLOT(sslErrors(QNetworkReply*, QList<QSslError>)));
}

/*
 * Token Methods
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

// Gets the token used by the QGeoloqi lib
QString QGeoloqi::getToken() {
    return this->token;
}

// Sets the token to be used by the QGeoloqi lib
void QGeoloqi::setToken(QString token) {
    this->token = token;
}


/*
 * API Methods
 * ============================================================================
 */

// Get the auth token using geoloqi username and password
QGeoloqiReply* QGeoloqi::getAuthToken(QString user, QString pass) {
    // Set up the parameters fo be sen URL Encoded
    QVector<QPair<QString,QString> > payloadData;
    payloadData.push_back(QPair<QString,QString>(QString("grant_type"), QString("password")));
    payloadData.push_back(QPair<QString,QString>(QString("username"), user));
    payloadData.push_back(QPair<QString,QString>(QString("password"), pass));
    payloadData.push_back(QPair<QString,QString>(QString("client_id"), this->client_id));
    payloadData.push_back(QPair<QString,QString>(QString("client_secret"), this->client_secret));
    QByteArray payload = encodeUrlEncoded(payloadData);

    QUrl url = QUrl(this->api_url % QString("oauth/token"));
    return post(url, payload);
}

QGeoloqiReply* QGeoloqi::getUsername() {
    QUrl url = QUrl(this->api_url % QString("account/username"));
    url.addQueryItem(QString("oauth_token"), this->token);
    return get(url);
}

QGeoloqiReply* QGeoloqi::getProfile() {
    QUrl url = QUrl(this->api_url % QString("account/profile"));
    url.addQueryItem(QString("oauth_token"), this->token);
    return get(url);
}

QGeoloqiReply* QGeoloqi::getLastLocation() {
    QUrl url = QUrl(this->api_url % QString("location/last"));
    url.addQueryItem(QString("oauth_token"), this->token);
    return get(url);
}

QGeoloqiReply* QGeoloqi::getHistory() {
    QUrl url = QUrl(this->api_url % QString("location/history"));
    url.addQueryItem(QString("oauth_token"), this->token);
    return get(url);
}

QGeoloqiReply* QGeoloqi::getPlaces(QString layer_id = "", QString include_unnamed = "", QString sort = "") {
    QUrl url = QUrl(this->api_url % QString("place/list"));
    url.addQueryItem(QString("oauth_token"), this->token);
    if (layer_id != "")
        url.addQueryItem(QString("layer_id"), layer_id);
    if (include_unnamed != "")
        url.addQueryItem(QString("include_unnamed"), include_unnamed);
    if (sort != "")
        url.addQueryItem(QString("sort"), sort);
    return get(url);
}

QGeoloqiReply* QGeoloqi::getNearbyPlaces(QString latitude = "", QString longitude = "", QString layer_id = "", QString distance = "") {
    QUrl url = QUrl(this->api_url % QString("place/nearby"));
    url.addQueryItem(QString("oauth_token"), this->token);
    if (latitude != "")
        url.addQueryItem(QString("latitude"), latitude);
    if (longitude != "")
        url.addQueryItem(QString("longitude"), longitude);
    if (layer_id != "")
        url.addQueryItem(QString("layer_id"), layer_id);
    if (distance != "")
        url.addQueryItem(QString("distance"), distance);
    return get(url);
}

QGeoloqiReply* QGeoloqi::getPlaceInfo(QString id) {
    QUrl url = QUrl(this->api_url % QString("place/info/") % id);
    url.addQueryItem(QString("oauth_token"), this->token);
    return get(url);
}

QGeoloqiReply* QGeoloqi::deletePlace(QString id) {
    QUrl url = QUrl(this->api_url % QString("place/delete/") % id);
    url.addQueryItem(QString("oauth_token"), this->token);
    return post(url, QByteArray());
}

/*
 * HTTP verbs
 * ============================================================================
 */

QGeoloqiReply* QGeoloqi::get(QUrl url) {
    QNetworkRequest request = QNetworkRequest(url);
    QNetworkReply* reply = manager->get(request);
    QGeoloqiReply* loqiply = new QGeoloqiReply(reply);
    connect(reply, SIGNAL(finished()), loqiply, SLOT(processReply()));
    return loqiply;
}

QGeoloqiReply* QGeoloqi::post(QUrl url, QByteArray payload) {
    QNetworkRequest request = QNetworkRequest(url);
    QNetworkReply* reply = manager->post(request, payload);
    QGeoloqiReply* loqiply = new QGeoloqiReply(reply);
    connect(reply, SIGNAL(finished()), loqiply, SLOT(processReply()));
    return loqiply;
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

void QGeoloqi::sslErrors(QNetworkReply * reply, QList<QSslError> errors) {
    QTextStream out(stdout);
    out << reply->readAll();
    QListIterator<QSslError> errorIterator(errors);

    while (errorIterator.hasNext()) {
        out << QString("SSL Error: %1\n").arg(errorIterator.next().errorString());
    }
    out << QString("%1 SSL Errors.\n").arg(errors.length());
}
