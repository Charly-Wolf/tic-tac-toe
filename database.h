#ifndef DATABASE_H
#define DATABASE_H

#include <QtSql>
#include <QDebug>
#include <QList>
#include "topplayer.h"

class Database
{
private:
    QSqlDatabase db;
    QString lastError;
    bool ready;
    QSqlQuery *abfrage(QString sql);
    void initDb();
    void addInitialData();
public:
    Database(QString dbFile);
    ~Database();

    QList<TopPlayer*> getAllPlayers();

    QString getLastError(); //DEBUG
};

#endif // DATABASE_H
