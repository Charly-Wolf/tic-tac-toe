/*
  * Datei:  klassenFuerTTT.cpp
  * Inhalt: Modell-Methoden für TTT
  * Autor:  Peter Gruening
  * Datum:  2024-02-04
  */

#include "klassenFuerTTT.h"

//------------Klasse Gewinner--------------//

/**
  * \brief
  *     Konstruktor - Setzt den Gewinnerstein und die erspielten Punkte
  *
  * \param	stein   Gewinnerstein
  * \param  punkte  erspielte Punkte
  */
Gewinner::Gewinner(STEIN stein, int punkte, QTime zeit)
{
    this->stein = stein;
    this->punkte = punkte;
    this->zeit = zeit;
}

/**
  * \brief
  *     Gibt den Gewinnerstein zurueck
  *
  * \return STEIN
  */
STEIN Gewinner::getStein()
{
    return this->stein;
}

/**
  * \brief
  *     Gibt die erspielten Punkte zurueck
  *
  * \return int
  */
int Gewinner::getPunkte()
{
    return this->punkte;
}

QTime Gewinner::getZeit() // Carlos Paredes
{
    return this->zeit;
}

/**
  * \brief
  *     Konstruktor - Setzt seinen Stein auf LEER und Zug auf (-1,-1)
  */
//-----------Zug---------------
Zug::Zug(): stein(STEIN::LEER), x(-1), y(-1)
{    
}

/**
  * \brief
  *     Konstruktor - Setzt seinen Stein und die Zugposition
  *
  * \param	stein   Gewinnerstein
  * \param  x       x-Pos
  * \param  y       y-Pos
  */
Zug::Zug(STEIN stein, int x, int y)
{
    this->stein = stein;
    this->x = x;
    this->y = y;
}

/**
  * \brief
  *     Getter fuer Stein
  *
  * \return STEIN
  */
STEIN Zug::getStein()
{
    return this->stein;
}

/**
  * \brief
  *     Getter fuer x-Pos
  *
  * \return int
  */
int Zug::getX()
{
    return this->x;
}

/**
  * \brief
  *     Getter fuer y-Pos
  *
  * \return int
  */
int Zug::getY()
{
    return this->y;
}

//----------------TicTacToe-------------
/**
  * \brief
  *     Konstruktor - macht nichts
  */
TicTacToe::TicTacToe()
{
}

/**
  * \brief
  *     Es wird geprueft, ob es ein Unentschieden gibt, weil kein Zug mehr moeglich ist.
  *
  * \return	bool: true = Unentschieden
  */
bool TicTacToe::pruefeUnentschieden()
{
    bool unentschieden = true;
    if (pruefeGewonnen() == LEER) { //wenn noc kein Sieger
        for(int x = 0; x < MAXX; x++) {
            for (int y = 0; y < MAXY; y++) {
                if (feld[y][x] == LEER) { //wenn noch ein Feld leer, dann noch kein Unentschieden
                    unentschieden = false;
                } //if
            } //for y
        } //for x
    } //if
    else {
        unentschieden = false;
    }
    return unentschieden;
}

/**
  * \brief
  *     Es wird gepreuft, ob es einen Sieger gibt.
  *
  * \return	STEIN: Der Stein des Siegers oder ein "leerer" Stein.
  */
STEIN TicTacToe::pruefeGewonnen()
{
    STEIN siegerstein = STEIN::LEER;
    int summe;

    //Pruefung horizontal
    for (int y = 0; y < MAXY && siegerstein == STEIN::LEER; y++) {
        summe = 0;
        for (int x = 0; x < MAXX; x++) { //Steine einer Zeile
            summe += feld[y][x];
        }
        if (summe == STEIN::KREIS * MAXX) {
            siegerstein = STEIN::KREIS;
        }
        else {
            if (summe == STEIN::KREUZ * MAXX) {
                siegerstein = STEIN::KREUZ;
            }
        }
    } //for y

    //Pruefung vertikal
    for (int x = 0; x <MAXX && siegerstein == STEIN::LEER; x++) {
        summe = 0;
        for (int y = 0; y < MAXY; y++) { //Steine eine Spalte
            summe += feld[y][x];
        }
        if (summe == STEIN::KREIS * MAXX) {
            siegerstein = STEIN::KREIS;
        }
        else {
            if (summe == STEIN::KREUZ * MAXX) {
                siegerstein = STEIN::KREUZ;
            }
        }
    } //for x

    if (siegerstein == STEIN::LEER) { //noch kein Sieger nach Spalten & Zeilen
        //Pruefung diagonal1
        summe = 0;
        for (int i = 0; i < MAXX; i++) { //ACHTUNG: nur bei quadratischen Feldern!
            summe += feld[i][i];
        }
        if (summe == STEIN::KREIS * MAXX) {
            siegerstein = STEIN::KREIS;
        }
        else {
            if (summe == STEIN::KREUZ * MAXX) {
                siegerstein = STEIN::KREUZ;
            }
        }

        if (siegerstein == STEIN::LEER) { //noch kein Sieger
            //Pruefung diagonal2
            summe = 0;
            for (int i = 0; i < MAXX; i++) {
                summe += feld[i][MAXX-i-1];
            }
            if (summe == STEIN::KREIS * MAXX) {
                siegerstein = STEIN::KREIS;
            }
            else {
                if (summe == STEIN::KREUZ * MAXX) {
                    siegerstein = STEIN::KREUZ;
                }
            }
        }
    } //noch kein Sieger nach Spalten & Zeilen


    return siegerstein;
}

/**
  * \brief
  *     Computer zieh je nach Level
  *
  * \return	ZUG: der gemachte Zug des Computer
  */
Zug TicTacToe::computerZieht()
{
    //HINWEIS: Computer ist immer STEIN::KREIS!!!

    Zug computerzug;
    int posX = -1; //zu setzender Zug
    int posY = -1;

    this->anzZuege++;

    if (this->level == 0) { //Computer setzt zufaellig
        this->computerZiehtZufaellig(posX,posY);
    }

    else if (this->level == 1) { //Computer setzt mit primitiver Taktik

        bool gefunden;

        gefunden = this->computerSuchtZweier(STEIN::KREIS,posX,posY); //Computer sucht eigenen 2er

        if (!gefunden) {
            gefunden = this->computerSuchtZweier(STEIN::KREUZ,posX,posY); //Computer sucht fremden 2er

            if (!gefunden) {
                this->computerZiehtZufaellig(posX,posY);
            }
        }
    }

    else if (this->level == 2) { //Computer mit KI
        //to do !!!!!!!!
    }

    feld[posY][posX] = STEIN::KREIS;
    computerzug = Zug(STEIN::KREIS,posX,posY);
    return computerzug;
}

/**
  * \brief
  *     Computer zieht zufaellig auf ein freies Feld
  *
  * \param  &posX   x-Pos fuer den 3er
  * \param  &posY   y-Pos fuer den 3er
  * \return	void
  */
void TicTacToe::computerZiehtZufaellig(int &posX, int &posY)
{
    do {
        posX = QRandomGenerator::global()->bounded(MAXX);
        posY = QRandomGenerator::global()->bounded(MAXY);
    } while (!this->stetzenMoeglich(posX,posY));
}


/**
  * \brief
  *     Es wird eine 2er-Kombination des uebergebenen Steins gesucht und die Position genannt,
  *     um daraus einen 3er zu machen
  *
  * \param	stein   nach welchen 2er wird gesucht
  * \param  &posX   x-Pos fuer den 3er
  * \param  &posY   y-Pos fuer den 3er
  * \return	bool: 2er gefunden oder nicht
  */
bool TicTacToe::computerSuchtZweier(STEIN stein, int &posX, int &posY)
{
    bool gefunden = false;
    int summe = 0;
    int leerX = -1;
    int leerY = -1;

    posX = -1;
    posY = -1;

    //horizontalen 2er mit  einem Leerfeld suchen
    for (int y = 0; y < MAXY && !gefunden; y++) {
        summe = 0;
        leerX = -1;
        leerY = -1;

        for (int x = 0; x < MAXX; x++) {
            summe += feld[y][x];
            if (this->stetzenMoeglich(x,y)) {//(feld[0][x] == STEIN::LEER)
                leerX = x;
                leerY = y;
            }
        }
        if (summe == stein * 2) { //2x stein, ein Feld frei
            posX = leerX;
            posY = leerY;
            gefunden = true;
        }
    }

    //vertikalen 2er mit einem Leerfeld suchen
    for (int x = 0; x < MAXX && !gefunden; x++) {
        summe = 0;
        leerX = -1;
        leerY = -1;

        for (int y= 0; y < MAXY; y++) {
            summe += feld[y][x];
            if (this->stetzenMoeglich(x,y)) {//(feld[0][x] == STEIN::LEER)
                leerX = x;
                leerY = y;
            }
        }
        if (summe == stein * 2) { //2x Stein, ein Feld frei
            posX = leerX;
            posY = leerY;
            gefunden = true;
        }
    }

    //Diagonal 1
    if (!gefunden) {
        summe = 0;
        leerX = -1;
        leerY = -1;
        for (int i = 0; i < MAXX; i++) { //geht nur bei quadratischen Feldern
            summe += feld[i][i];
            if (this->stetzenMoeglich(i,i)) {//(feld[0][x] == STEIN::LEER)
                leerX = i;
                leerY = i;
            }
        }
        if (summe == stein * 2) { //2x Stein, ein Feld frei
            posX = leerX;
            posY = leerY;
            gefunden = true;
        }
    }

    //Diagonal 2
    if(!gefunden) {
        summe = 0;
        leerX = -1;
        leerY = -1;
        for (int i = 0; i < MAXX; i++) { //geht nur bei quadratischen Feldern
            summe += feld[MAXY-i-1][i];
            if (this->stetzenMoeglich(i,MAXY-i-1)) {//(feld[0][x] == STEIN::LEER)
                leerX = i;
                leerY = MAXY-i-1;
            }
        }
        if (summe == stein * 2) { // 2x Stein, ein Feld frei
            posX = leerX;
            posY = leerY;
            gefunden = true;
        }
    }
    return gefunden;
}

/**
  * \brief
  *     Es wird geprueft, ob das Spiel beendet ist. Es sind bei Spielende keine Zuege mehr moeglich.
  *
  * \param	&spielende: true = Spiel ist beendet
  * \return	GEWINNER
  */
Gewinner TicTacToe::pruefeSpielende(bool &spielende)
{
    Gewinner sieger(STEIN::LEER,0);

    spielende = false;

    if (this->pruefeUnentschieden()) {
        spielende = true;
    }
    else {
        STEIN siegerstein =  pruefeGewonnen();
        if (siegerstein != LEER) {
            int punkte = (10.0 / this->anzZuege * 100000 - this->spielzeit.elapsed()) / 100;
            punkte *= (this->level + 1) / 3.0;
            QTime elapsedTime = QTime(0,0,0).addMSecs(this->spielzeit.elapsed());
            sieger = Gewinner(siegerstein, punkte, elapsedTime);
            spielende = true;
        }
    }

    return sieger;
}

/**
  * \brief
  *     Reset und Start des Spieles.
  *     Es wird zufaellig entschieden, ob Coumpter oder Spieler beginnt.
  *     Falls der Computer beginnt, wird der erste Zug zurueckgegeben.
  *
  *     to do: LEVEL 2 IMPLEMENTIEREN !!!!!!
  *
  * \param	level:int   Schwierigkeitsgrad, derzeit nur 0 und 1 implementiert
  * \param  debug:bool true=Debugmode mit Ausgaben auf der Konsole
  * \return	ZUG
  */
Zug TicTacToe::starteSpiel(int level, bool debug)
//level: 0 = Zufallszuege
//       1 = eigenen Zweier spielen oder Gegner-Zweier finden und Dreier blockieren verhindern
//       2 = "echte" KI -> to do in computerZieht() !!!!
{        
    Zug zug;

    if (level > 1) { //bisher nur 0 und 1 implementiert, aendern bei weiteren Leveln
        level = 1;
    }
    else {
        if (level < 0) {
            level = 0;
        }
    }

    this->level = level;
    this->debug = debug;

    this->anzZuege = 0;
    this->spielzeit.start();

    //Feld leeren
    for (int y = 0; y < MAXY; y++) {
        for (int x = 0; x < MAXX; x++) {
            this->feld[y][x] = STEIN::LEER;
        }
    }

    //Starter per Zufall bestimmen
    int starter = QRandomGenerator::global()->bounded(2); //0=Mensch startet, 1=Computer startet

    if (starter == 0) { //Mensch startet
        Zug tmpZug(STEIN::LEER,0,0);
        zug = tmpZug;
    }

    else { //Computer startet, Computer ist immer KREIS
        Zug tmpZug(KREIS,
                   QRandomGenerator::global()->bounded(MAXX),
                   QRandomGenerator::global()->bounded(MAXY));
        zug = tmpZug;
        this->feld[zug.getY()][zug.getX()] = STEIN::KREIS;
        this->anzZuege++;
    }

    if (this->debug) {
        qDebug() << "Spielstart";
        debugFeld();
        qDebug() << "";
    }

    return zug;
}

/**
  * \brief
  *     Prueft, ob ein Stein setztbar ist
  *
  * \param  posX   x-Pos
  * \param  posY   y-Pos
  * \return	bool   true=Feld ist vorhanden und leer
  */
bool TicTacToe::stetzenMoeglich(int x, int y)
{
    bool ok = false;
    if (x >= 0 && x < MAXX && y >= 0 && y < MAXY) {
        ok = (feld[y][x] == STEIN::LEER);
    }
    return ok;
}

/**
  * \brief
  *     Setzt, wenn moeglich, einen Stein des Spielers auf (x,y) und gibt den Gegen-Zug des Computers zurueck
  *     Zaehlt die Anzahl der Zuege
  *     Gibt im Debug-Mode die beiden Zuege und das geaenderte Spielfeld auf der Konsole aus.
  *
  * \param	stein
  * \param  x   x-Pos fuer den 3er
  * \param  y   y-Pos fuer den 3er
  * \return	Zug  enthaelt den Gegenzug
  */
Zug TicTacToe::steinSetzen(STEIN stein, int x, int y)
{
    //fuer debug-mode !!!!!!
    if (this->debug) {
        debugFeld();
    }

    Zug gegenzug;
    this->anzZuege++;

    if (this->stetzenMoeglich(x,y)) {
        feld[y][x] = stein;
    }
    if (!this->pruefeUnentschieden() && this->pruefeGewonnen() == STEIN::LEER) {
        gegenzug = this->computerZieht();
    }

    //fuer debug-mode !!!!!!
    if (this->debug) {
        qDebug() << "X-Zug: " << x << " " << y;
        qDebug() << "O-Zug: " << gegenzug.getX() << " " << gegenzug.getY();

        debugFeld();
        qDebug() << "";
    }

    return gegenzug;
}

/**
  * \brief
  *     Gibt das Spielfeld in der Konsole aus
  *
  */
void TicTacToe::debugFeld() {
    QString z;
    for (int y = 0; y < MAXY; y++ ) {
        z.clear();
        for (int x = 0; x < MAXX; x++) {
            switch (feld[y][x]){
            case STEIN::LEER: z += "."; break;
            case STEIN::KREIS: z += "O"; break;
            case STEIN::KREUZ: z += "X"; break;

            }
        } // for x
        qDebug() << z;
    }
}


