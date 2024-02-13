#include "database.h"

Database::Database(QString dbFile)
{
    this->ready = false;
    this->db = (QSqlDatabase::addDatabase("QSQLITE"));
    this->db.setDatabaseName(dbFile);
    this->ready = db.open();
    this->lastError = db.lastError().text();

    this->initDb();

    this->db.close();
}

Database::~Database()
{
    this->db.close();
}

QList<TopPlayer *> Database::getAllPlayers()
{
    qDebug() << "---GET ALL PLAYERS from DB";

    QList<TopPlayer*> topPlayers;
    bool ok = false;
    QSqlQuery query;

    QString queryString = "SELECT * FROM Player";

    // TODO: this is just for testing:
    this->ready = this->db.open();
    if (this->ready) {
        this->ready = query.exec(queryString);
        this->lastError = query.lastError().text();

        ok = true; // TODO Fix this

        while(ok) {
            QString nickname = query.value("nickname").toString();
            qDebug() << "NICKNAME: " << nickname;
            int score = query.value("score").toInt();
            qDebug() << "SCORE: " << score;
            ok = query.next();

            TopPlayer* p = new TopPlayer(nickname, score);
            topPlayers.append(p);
            delete p;
            if (ok) qDebug() << "NEXT ROW IN DB!\n----";
        }
    }


//    delete query;
    return topPlayers;
}

void Database::initDb()
{
    qDebug() << "Initializing DB";
    QSqlQuery query;

    if (query.exec("SELECT * FROM Player LIMIT 1")) {
        qDebug() << "Table already exists";
        return;
    }

    QString queryString = "CREATE TABLE IF NOT EXISTS Player ("
                          "id INTEGER PRIMARY KEY AUTOINCREMENT,"
                          "nickname TEXT NOT NULL,"
                          "score INTEGER)";

    if (!query.exec(queryString))
    {
        qDebug() << "Error: Failed to create table Player: " << query.lastError().text();
        return;
    }

    this->addInitialData();

    qDebug() << "Table Player created!";
}

void Database::addInitialData()
{
    qDebug() << "Adding inital data to DB";
    QSqlQuery query;

    QString queryString = "INSERT INTO Player (nickname, score)"
                          "VALUES ('JonSnow', 632), "
                          "('TheBestPlayer', 899), "
                          "('SansaStark', 400)";

    if (!query.exec(queryString))
    {
        qDebug() << "Error: Failed to insert initial data: " << query.lastError().text();
        return;
    }

    qDebug() << "Initial data was added to the DB!";
}
