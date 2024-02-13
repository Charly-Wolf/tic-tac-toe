/*
  * Datei:  topPlayer.cpp
  * Inhalt: Top Player Methoden
  * Autor:  Carlos Paredes
  * Datum:  2024-02-11
  */

#include "topPlayer.h"

TopPlayer::TopPlayer(QString nickname, int score)
{
    this->nickname = nickname;
    this->score = score;
}

TopPlayer::~TopPlayer()
{

}

QString TopPlayer::getNickname()
{
    return this->nickname;
}

int TopPlayer::getScore()
{
    return this->score;
}

QString TopPlayer::toString()
{
    return getNickname() + ": " + QString::number(getScore());
}

void TopPlayer::setScore(int score)
{
    this->score = score;
}
