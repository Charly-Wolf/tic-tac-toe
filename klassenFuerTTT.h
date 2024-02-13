/**
  * Datei:  klassenFuerTTT.h
  * Inhalt: Modell-Klassen für TTT
  * Autor:  Peter Gruening
  * Modifizierungen: Carlos Paredes
  * Datum:  2024-02-04
  */

#ifndef KLASSENFUERTTT_H
#define KLASSENFUERTTT_H

#include <QTime>
#include <QRandomGenerator>
#include <QDebug>

enum STEIN : int {LEER=0,KREUZ=1,KREIS=10}; //Computer ist immer STEIN::KREIS!!! \enum

class Gewinner {
private:
    STEIN stein;
    int punkte;
    QTime zeit; // Carlos Paredes
public:
    Gewinner(STEIN stein, int punkte = 0,
             QTime zeit = QTime(0,0,0)); // Carlos Paredes
    STEIN getStein();
    int getPunkte();
    QTime getZeit(); // Carlos Paredes
};

class Zug {
private:
    STEIN stein;
    int x;
    int y;
public:
    Zug();
    Zug(STEIN stein, int x, int y);
    STEIN getStein();
    int getX();
    int getY();
};

class TicTacToe {
private:
    static const int MAXX = 3;
    static const int MAXY = 3;
    STEIN feld[MAXY][MAXX] = {{LEER}};
    int level;
    int anzZuege;
    QTime spielzeit;
    bool debug = false;

    bool pruefeUnentschieden();
    STEIN pruefeGewonnen();
    Zug computerZieht();
    void computerZiehtZufaellig(int &posX, int &posY);
    bool computerSuchtZweier(STEIN stein, int &posX, int &posY);
    void debugFeld();

public:
    TicTacToe();
    Zug starteSpiel(int level, bool debug = false);
    bool stetzenMoeglich(int x, int y);
    Zug steinSetzen(STEIN stein, int x, int y);
    Gewinner pruefeSpielende(bool &spielende);
};

#endif // KLASSENFUERTTT_H
