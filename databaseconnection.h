#ifndef DATABASECONNECTION_H
#define DATABASECONNECTION_H

#include <QSqlDatabase>
#include <QtSql>

/**
    Classe di connessione al database.
*/
class DatabaseConnection
{
public:
    /**
        Costruttore di default che si connette automaticamente al database MySQL su localhost con
        nome database "Recipe1M" e username e password di default.
    */
    DatabaseConnection();

    /**
        Costruttore si connette al database MySQL con i parametri passati in ingresso.
        @param hostname Indirizzo IP e porta della macchina su cui risiede il database.
        @param databasename Nome del database a cui è richiesto collegarsi.
        @param username Nome utente per accedere al database.
        @param password Password per accedere al database.
        @param sqldatabase Tipologia del database SQL ("QMYSQL" di default).
    */
    DatabaseConnection(QString hostname, QString databasename, QString username, QString password, QString sqldatabase = "QMYSQL");

    /**
        Metodo che verifica la connessione al database aprendola e chiudendola.
        @return Ritorna un booleano che ha valore true se la connessione è stata stabilita correttamente, false altrimenti.
    */
    bool connectionOk();

    /**
        Metodo che effettua una query al database.
        @param query Prende in input una QString contenente la stringa.
        @return Ritorna il risultato della query come QSqlQuery.
    */
    QSqlQuery executeQuery(QString query);

private:
    QSqlDatabase db;

};

#endif // DATABASECONNECTION_H
