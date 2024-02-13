/**
  * Datei:  frmmain.h
  * Inhalt: Main Form Klasse
  * Autor:  Carlos Paredes
  * Datum:  2024-02-11
  */

#ifndef FRMMAIN_H
#define FRMMAIN_H

#include <QWidget>
#include <QPushButton>
#include "klassenFuerTTT.h"
#include "topPlayer.h"
#include "topPlayersList.h"
#include "modusEnum.h"

QT_BEGIN_NAMESPACE
namespace Ui { class FrmMain; }
QT_END_NAMESPACE



class FrmMain : public QWidget
{
    Q_OBJECT

public:
    FrmMain(QWidget *parent = nullptr);
    ~FrmMain();

private slots:
    void on_btnPlay_clicked();
    void on_btnTopLeft_clicked();
    void on_radBtnEasy_clicked();
    void on_radBtnNormal_clicked();
    void on_btnExit_clicked();
    void on_btnTopCenter_clicked();
    void on_btnTopRight_clicked();
    void on_btnCenterLeft_clicked();
    void on_btnCenter_clicked();
    void on_btnCenterRight_clicked();
    void on_btnBottomLeft_clicked();
    void on_btnBottomCenter_clicked();
    void on_btnBottomRight_clicked();
    void on_btnExit2_clicked();
    void on_btnPlayAgain_clicked();
    void on_btnRecordScore_clicked();
    void on_btnNotRecordScore_clicked();

    void on_btnBackToNickname_clicked();

    void on_btnNotRecordScore2_clicked();

private:
    Ui::FrmMain *ui;
    TicTacToe* ticTacToe;
    QTimer* tmr;
    TopPlayersList* topPlayersList;
    QPushButton* gridButtons[3][3];
    MODUS currentModus = MODUS::HOME;
    int difficulty = 0;
    int moveNumber = 1;

    void initUI();
    void initGridButtons();
    void setDifficulty(int lvl);
    void setHomeModus();
    void setPlayingModus();
    void setInputNicknameModus();
    void setWaitingForReplayModus(STEIN winnerToken);
    void setWarningEmptyNicknameModus();
    void playerMakesMove(int x, int y);
    void computerMakesMove(int x, int y);
    void createInitialTopPlayers();
    void displayTopPlayers();
    void keyPressEvent(QKeyEvent* event) override;
};
#endif // FRMMAIN_H
