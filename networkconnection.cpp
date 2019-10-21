#include "networkconnection.h"

#include <QEventLoop>

NetworkConnection::NetworkConnection() : QObject()
{
    nam = new QNetworkAccessManager(this);
}

QNetworkReply* NetworkConnection::connection(QString image){
    QUrl url(image);
    QNetworkReply* reply = nam->get(QNetworkRequest(url));
    QEventLoop eventLoop;
    connect(reply,SIGNAL(finished()),&eventLoop,SLOT(quit()));
    eventLoop.exec();
    return reply;
}
