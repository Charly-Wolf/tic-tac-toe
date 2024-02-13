/*
  * Datei:  topPlayerList.cpp
  * Inhalt: Top Player List Container Methoden
  * Autor:  Carlos Paredes
  * Datum:  2024-02-11
  */

#include "topPlayersList.h"

TopPlayersList::TopPlayersList(QString dbFile)
{
    this->db = new Database(dbFile);

    //TODO
//    this->topPlayers = this->db->getAllPlayers();
}

TopPlayersList::~TopPlayersList()
{
    for (TopPlayer* p : topPlayers) {
        delete p;
    }
}

void TopPlayersList::addTopPlayer(TopPlayer* topPlayer)
{
    topPlayers << topPlayer;
    sortPlayersDesc();
}

TopPlayer* TopPlayersList::getTopPlayer(int index)
{
    if (index >= 0 && index < getSize())
    {
        return topPlayers[index];
    }
    return nullptr;
}

int TopPlayersList::getSize()
{
    return topPlayers.size();
}

void TopPlayersList::sortPlayersDesc()
{
    int amount = getSize();
    bool sorted = false;

    for (int i = 0; i < amount - 1 && !sorted; i++) {
        sorted = true;
        for (int j = 0; j < amount - 1 - i; j++) {
            if (topPlayers[j]->getScore() < topPlayers[j+1]->getScore()) {
                topPlayers.swap(j, j+1);
                sorted = false;
            }
        }
    }
}
