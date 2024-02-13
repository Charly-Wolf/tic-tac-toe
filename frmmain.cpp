/*
  * Datei:  frmmain.cpp
  * Inhalt: Main Form Methoden
  * Autor:  Carlos Paredes
  * Datum:  2024-02-11
  */

#include "frmmain.h"
#include "ui_frmmain.h"

FrmMain::FrmMain(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::FrmMain)
{
    ui->setupUi(this);

    QString dbFile = "dbTicTacToe.sqlite";
    setWindowTitle("TicTacToe Game");

    ticTacToe = new TicTacToe();
    topPlayersList = new TopPlayersList(dbFile);

    createInitialTopPlayers();
    displayTopPlayers();
    initGridButtons();
    setHomeModus();
}

FrmMain::~FrmMain()
{
    delete ui;
    delete topPlayersList;
}


void FrmMain::on_btnPlay_clicked()
{
    setPlayingModus();
    Zug initialMove = ticTacToe->starteSpiel(difficulty, true);
    if (initialMove.getStein() == STEIN::KREIS) {
        computerMakesMove(initialMove.getX(), initialMove.getY());
    }
}


void FrmMain::on_radBtnEasy_clicked()
{
    setDifficulty(0);
}


void FrmMain::on_radBtnNormal_clicked()
{
    setDifficulty(1);
}


void FrmMain::on_btnExit_clicked()
{
    QCoreApplication::exit();
}

void FrmMain::setDifficulty(int lvl)
{
    difficulty = lvl;
    QString difficultyString = "";
    switch (lvl) {
    case 1:
        difficultyString = "Normal";
        break;
    default:
        difficultyString = "Easy";
    }
    ui->leDifficulty->setText(difficultyString);
}

void FrmMain::setHomeModus()
{
    currentModus = MODUS::HOME;
    ui->leNickname->clearFocus();
    ui->widgetHome->show();
    ui->widgetGame->hide();
    ui->groupNickname->hide();
    ui->widgetOverlayModal->hide();
    ui->widgetNotifications->hide();
    ui->groupReplay->hide();
    ui->groupWarningEmptyNickname->hide();
}

void FrmMain::setPlayingModus()
{
    currentModus = MODUS::PLAYING;
    ui->leNickname->clearFocus();
    ui->groupKeysInfo->show();
    ui->lblNotifications->setText("Make your move!");
    moveNumber = 1;
    ui->leTurnNumber->setText(QString::number(moveNumber));
    ui->widgetGame->setEnabled(true);
    ui->widgetOverlayModal->hide();
    ui->widgetGame->show();
    ui->widgetHome->hide();
    ui->widgetNotifications->show();

    int const MAXX = 3;
    int const MAXY = 3;

    for (int i = 0; i < MAXX; i++) {
        for (int j = 0; j < MAXY; j++) {
            gridButtons[i][j]->setText("");
        }
    }
}

void FrmMain::setInputNicknameModus()
{
    currentModus = MODUS::INPUT_NICKNAME;
    ui->widgetOverlayModal->show();
    ui->widgetOverlayModal->raise();
    ui->widgetNotifications->raise();
    ui->groupNickname->show();
    ui->groupNickname->raise();
    ui->leNickname->setFocus();
    ui->groupWarningEmptyNickname->hide();
    ui->lblNotifications->setText(("You won 😁"));
}

void FrmMain::setWaitingForReplayModus(STEIN winnerToken)
{
    currentModus = MODUS::WAITING_FOR_REPLAY;
    ui->groupReplay->setTitle("Game Over");
    ui->widgetOverlayModal->show();
    ui->widgetOverlayModal->raise();
    ui->widgetNotifications->raise();
    ui->lblNotifications->setText(winnerToken == STEIN::KREIS ? "Computer won 😢" : "Draw 😑");
    ui->groupKeysInfo->hide();
    ui->groupReplay->show();
    ui->groupReplay->raise();
}

void FrmMain::setWarningEmptyNicknameModus()
{
    currentModus = MODUS::WARNING_EMPTY_NICKNAME;
    ui->groupWarningEmptyNickname->show();
    ui->widgetOverlayModal->raise();
    ui->groupWarningEmptyNickname->raise();
}

void FrmMain::initGridButtons()
{
    gridButtons[0][0] = ui->btnTopLeft;
    gridButtons[0][1] = ui->btnTopCenter;
    gridButtons[0][2] = ui->btnTopRight;
    gridButtons[1][0] = ui->btnCenterLeft;
    gridButtons[1][1] = ui->btnCenter;
    gridButtons[1][2] = ui->btnCenterRight;
    gridButtons[2][0] = ui->btnBottomLeft;
    gridButtons[2][1] = ui->btnBottomCenter;
    gridButtons[2][2] = ui->btnBottomRight;
}

void FrmMain::playerMakesMove(int x, int y)
{
    if (ticTacToe->stetzenMoeglich(x, y))
    {
        QPushButton* gridBtn = gridButtons[x][y];
        Zug computerMove = ticTacToe->steinSetzen(STEIN::KREUZ, x, y);

        gridBtn->setText("❎");
        gridBtn->setStyleSheet(gridBtn->styleSheet() + "color: green;");

        bool isGameOver;
        Gewinner winner = ticTacToe->pruefeSpielende(isGameOver);

        if (isGameOver) {
            ui->widgetGame->setDisabled(true);

            if (winner.getStein() == STEIN::KREUZ) {

                setInputNicknameModus();
                ui->leScore->setText(QString::number(winner.getPunkte()));
                ui->leTime->setText(winner.getZeit().toString("mm:ss"));
                ui->leAmountMovesWinner->setText(QString::number(moveNumber));
                ui->leDifficultyWinner->setText(ui->leDifficulty->text());
            }
            else {
                setWaitingForReplayModus(winner.getStein());
                if (winner.getStein() == STEIN::KREIS) computerMakesMove(computerMove.getX(),computerMove.getY());

            }
            return;
        }

        computerMakesMove(computerMove.getX(),computerMove.getY());

    } else {
        // TODO: Message somewhere on the screen
        qDebug() << "Movement not allowed: this place is already occupied by another token";
    }
    moveNumber++;
    ui->leTurnNumber->setText(QString::number(moveNumber));
}

void FrmMain::computerMakesMove(int x, int y)
{
    QPushButton* gridBtn = gridButtons[x][y];
    gridBtn->setText("⭕");
    gridBtn->setStyleSheet(gridBtn->styleSheet() + "color: red;");
}

void FrmMain::createInitialTopPlayers()
{
    TopPlayer* p1 = new TopPlayer("JonSnow", 632);
    topPlayersList->addTopPlayer(p1);
    TopPlayer* p2 = new TopPlayer("TheBestPlayer", 899);
    topPlayersList->addTopPlayer(p2);
    TopPlayer* p3 = new TopPlayer("SansaStark", 400);
    topPlayersList->addTopPlayer(p3);
}

void FrmMain::displayTopPlayers()
{
    ui->lwScoreboard->clear();
    int size = topPlayersList->getSize();
    if (size == 0) {
        ui->lwScoreboard->addItem("No top players to display");
    }
    else {
        TopPlayer* p;
        for (int i = 0; i < size; i++)
        {
            p = topPlayersList->getTopPlayer(i);
            if (p) {
                ui->lwScoreboard->addItem(QString::number(i+1) + ". " +  p->toString());
            }
            else {
                qDebug() << "Top player with index " << i <<  " does not exist";
            }
        }
    }
}

void FrmMain::keyPressEvent(QKeyEvent* event)
{
    int key = event->key();

    switch (currentModus) {
    case (MODUS::INPUT_NICKNAME):
        if (key == Qt::Key_Enter || key == Qt::Key_Return) {
            FrmMain::on_btnRecordScore_clicked();

        }
        else if (key == Qt::Key_Escape) {
            FrmMain::on_btnNotRecordScore_clicked();
        }
        break;
    case (MODUS::PLAYING):
        switch (key) {
        case (Qt::Key_F1):
            ui->lbl1->isHidden() ? ui->lbl1->show() : ui->lbl1->hide();
            ui->lbl2->isHidden() ? ui->lbl2->show() : ui->lbl2->hide();
            ui->lbl3->isHidden() ? ui->lbl3->show() : ui->lbl3->hide();
            ui->lbl4->isHidden() ? ui->lbl4->show() : ui->lbl4->hide();
            ui->lbl5->isHidden() ? ui->lbl5->show() : ui->lbl5->hide();
            ui->lbl6->isHidden() ? ui->lbl6->show() : ui->lbl6->hide();
            ui->lbl7->isHidden() ? ui->lbl7->show() : ui->lbl7->hide();
            ui->lbl8->isHidden() ? ui->lbl8->show() : ui->lbl8->hide();
            ui->lbl9->isHidden() ? ui->lbl9->show() : ui->lbl9->hide();
            break;
        case (Qt::Key_7):
            FrmMain::on_btnTopLeft_clicked();
            break;
        case (Qt::Key_8):
            FrmMain::on_btnTopCenter_clicked();
            break;
        case (Qt::Key_9):
            FrmMain::on_btnTopRight_clicked();
            break;
        case (Qt::Key_4):
            FrmMain::on_btnCenterLeft_clicked();
            break;
        case (Qt::Key_5):
            FrmMain::on_btnCenter_clicked();
            break;
        case (Qt::Key_6):
            FrmMain::on_btnCenterRight_clicked();
            break;
        case (Qt::Key_1):
            FrmMain::on_btnBottomLeft_clicked();
            break;
        case (Qt::Key_2):
            FrmMain::on_btnBottomCenter_clicked();
            break;
        case (Qt::Key_3):
            FrmMain::on_btnBottomRight_clicked();
            break;
        }
        break;
    case(MODUS::HOME):
        if (key == Qt::Key_Enter || key == Qt::Key_Return) {
            FrmMain::on_btnPlay_clicked();
        }
        if (key == Qt::Key_2) {
            ui->radBtnNormal->setChecked(true);
            FrmMain::on_radBtnNormal_clicked();
        }
        if (key == Qt::Key_1) {
            ui->radBtnEasy->setChecked(true);
            FrmMain::on_radBtnEasy_clicked();
        }
        if (key == Qt::Key_Escape) {
            FrmMain::on_btnExit_clicked();
        }
        break;
    case(MODUS::WAITING_FOR_REPLAY):
        if (key == Qt::Key_Enter || key == Qt::Key_Return) {
            FrmMain::on_btnPlayAgain_clicked();
        }
        else if (key == Qt::Key_Escape) {
            FrmMain::on_btnExit2_clicked();
        }
        break;
    case(MODUS::WARNING_EMPTY_NICKNAME):
        if (key == Qt::Key_Enter || key == Qt::Key_Return) {
            FrmMain::on_btnNotRecordScore2_clicked();
        }
        else if (key == Qt::Key_Escape) {
            FrmMain::on_btnBackToNickname_clicked();
        }
        break;
    }
}

void FrmMain::on_btnTopLeft_clicked()
{
    playerMakesMove(0, 0);
}

void FrmMain::on_btnTopCenter_clicked()
{
    playerMakesMove(0, 1);
}


void FrmMain::on_btnTopRight_clicked()
{
    playerMakesMove(0, 2);
}


void FrmMain::on_btnCenterLeft_clicked()
{
    playerMakesMove(1, 0);
}


void FrmMain::on_btnCenter_clicked()
{
    playerMakesMove(1, 1);
}


void FrmMain::on_btnCenterRight_clicked()
{
    playerMakesMove(1, 2);
}


void FrmMain::on_btnBottomLeft_clicked()
{
    playerMakesMove(2, 0);
}


void FrmMain::on_btnBottomCenter_clicked()
{
    playerMakesMove(2, 1);
}


void FrmMain::on_btnBottomRight_clicked()
{
    playerMakesMove(2, 2);
}


void FrmMain::on_btnExit2_clicked()
{
    FrmMain::on_btnExit_clicked();
}


void FrmMain::on_btnPlayAgain_clicked()
{
    setHomeModus();
}


void FrmMain::on_btnRecordScore_clicked()
{
    // TODO: max length
    // TODO: trim
    QString nickName = ui->leNickname->text();
    ui->leTime->clear();

    if (!nickName.isEmpty()) {
        int winnerScore = ui->leScore->text().toInt();
        int size = topPlayersList->getSize();;
        if (size == 0) {
            topPlayersList->addTopPlayer(new TopPlayer(nickName, winnerScore));
        }
        else {
            TopPlayer* p;
            bool isPlayerOnTheList = false;
            for (int i = 0; i < size; i++)
            {
                p = topPlayersList->getTopPlayer(i);
                if (p) {
                    if (p->getNickname().toLower() == nickName.toLower()) {
                        isPlayerOnTheList = true;
                        if (p->getScore() <  winnerScore) {
                            p->setScore(winnerScore);
                            topPlayersList->sortPlayersDesc();
                        }
                        break;
                    }
                    else {
                        isPlayerOnTheList = false;
                    }
                }
                else {
                    qDebug() << "Top player with index " << i <<  " does not exist";
                }
            }

            if (!isPlayerOnTheList) {
                topPlayersList->addTopPlayer(new TopPlayer(nickName, winnerScore));
            }
        }
        displayTopPlayers();
        setHomeModus();
        ui->leNickname->clearFocus();
    }
    else {
        setWarningEmptyNicknameModus();
    }
}


void FrmMain::on_btnNotRecordScore_clicked()
{
    setHomeModus();
//    ui->groupNickname->hide();
    qDebug() << "TODO warning!";
}

void FrmMain::on_btnBackToNickname_clicked()
{
    setInputNicknameModus();
}


void FrmMain::on_btnNotRecordScore2_clicked()
{
    setHomeModus();
}

