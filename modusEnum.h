/**
  * Datei:  modusEnum.h
  * Inhalt: Enum mit Spielmodi
  * Autor:  Carlos Paredes
  * Datum:  2024-02-11
  */

#ifndef MODUSENUM_H
#define MODUSENUM_H

enum MODUS : int {
    HOME = 0,
    PLAYING = 1,
    INPUT_NICKNAME = 2,
    WAITING_FOR_REPLAY = 3,
    WARNING_EMPTY_NICKNAME = 4
};

#endif // MODUSENUM_H
