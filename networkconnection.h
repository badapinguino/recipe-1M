#ifndef NETWORKCONNECTION_H
#define NETWORKCONNECTION_H

#include <QNetworkAccessManager>

class NetworkConnection : public QObject
{
    Q_OBJECT
public:
    NetworkConnection();
    QNetworkReply* connection(QString image);
private:
    QNetworkAccessManager *nam;
//private slots:
    //connect();
};

#endif // NETWORKCONNECTION_H
