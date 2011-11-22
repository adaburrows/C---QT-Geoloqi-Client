#include <QtGui/QApplication>
#include "loqiwindow.h"
#include "qgeoloqi.h"
#include "config_vars.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    LoqiWindow w;
    QGeoloqi* loqi = new QGeoloqi(QString(client_id),QString(client_secret));


/*
    // Test of URL Encoding/Decoding
    QTextStream out(stdout);
    QByteArray querystring = QByteArray("greeting=hello&name=jill");
    QVector<QPair<QString,QString> > decoded = loqi->decodeUrlEncoded(querystring);
    QByteArray encoded = loqi->encodeUrlEncoded(decoded);
    out << QString(encoded);
*/

    w.show();

    loqi->getAuthToken(QString("jburrows"),QString("hehe"));
    loqi->setToken(QString(permanent_token));
    loqi->getUsername();
    loqi->getProfile();
    loqi->getLastLocation();
    loqi->getHistory();

    return a.exec();
}
