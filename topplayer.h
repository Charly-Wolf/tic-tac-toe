/**
  * Datei:  topPlayer.h
  * Inhalt: Top Player Klasse
  * Autor:  Carlos Paredes
  * Datum:  2024-02-11
  */

#ifndef TOPPLAYER_H
#define TOPPLAYER_H

#include <QString>

class TopPlayer
{
public:
    TopPlayer(QString nickname, int score);
    ~TopPlayer();
    QString getNickname();
    int getScore();
    QString toString();
    void setScore(int score);
private:
    QString nickname;
    int score;
};

#endif // TOPPLAYER_H
