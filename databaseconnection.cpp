#include "databaseconnection.h"

DatabaseConnection::DatabaseConnection(){
    db = QSqlDatabase::addDatabase("QMYSQL");
    db.setHostName("localhost");
    db.setDatabaseName("Recipe1M");
    db.setUserName("root");
    db.setPassword("root");
}

DatabaseConnection::DatabaseConnection(QString hostname, QString databasename, QString username, QString password, QString sqldatabase){
    db = QSqlDatabase::addDatabase(sqldatabase);
    db.setHostName(hostname);
    db.setDatabaseName(databasename);
    db.setUserName(username);
    db.setPassword(password);
}

bool DatabaseConnection::connectionOk(){
    bool ok = db.open();
    db.close();
    return ok;
}

QSqlQuery DatabaseConnection::executeQuery(QString query){
    db.open();
    QSqlQuery richiesta;
    richiesta.exec(query);
    db.close();
    return richiesta;
}
