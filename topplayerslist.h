/**
  * Datei:  topPlayerList.h
  * Inhalt: Top Player List Container Klasse
  * Autor:  Carlos Paredes
  * Datum:  2024-02-11
  */

#ifndef TOPPLAYERSLIST_H
#define TOPPLAYERSLIST_H

#include <QList>
#include "topplayer.h"
#include "database.h"

class TopPlayersList
{
public:
    TopPlayersList(QString dbFile);
    ~TopPlayersList();
    void addTopPlayer(TopPlayer* topPlayer);
    TopPlayer* getTopPlayer(int index);
    int getSize();
    void sortPlayersDesc();

private:
    QList<TopPlayer*> topPlayers;
    Database* db;
};

#endif // TOPPLAYERSLIST_H
