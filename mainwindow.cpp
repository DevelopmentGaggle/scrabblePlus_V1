#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include "BoardTile.h"
#include "Game.h"
#include "blankpopup.h"
#include <QtWidgets>
#include <QtMath>

#include <iostream>
using namespace std;

MainWindow::MainWindow(Game* game, QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    this->game = game;
    Tile** board = this->game->GetBoard();
    this->board = board;
    update_player();

    //update_window();

    int RowCount = 15;
    int corner_offset = 5;

    QGraphicsScene *graphic = new QGraphicsScene( this );
    this->graphic = graphic;
    graphic->setSceneRect(0, 0, RowCount*(50+corner_offset)+corner_offset, RowCount*(50+corner_offset)+corner_offset);

    graphic->setItemIndexMethod(QGraphicsScene::NoIndex);

    for (int i = 0; i < RowCount; ++i) {
        for (int j =0; j < RowCount; ++j) {
            BoardTile *board_tile = new BoardTile(board[i][j]);
            board_tile->setPos((corner_offset + j * 55), (corner_offset + i * 55));
            graphic->addItem(board_tile);
        }
    }

    this->setWindowTitle("ScrabblePlus");
    this->setWindowIcon(QIcon(":/Resources/BoardAttributes/star.png"));

    ui->scrabble_board->setScene(graphic);
}

void MainWindow::update_window() {
    int RowCount = 15;
    int corner_offset = 5;
    //graphic->clear();
    graphic->setSceneRect(0, 0, RowCount*(50+corner_offset)+corner_offset, RowCount*(50+corner_offset)+corner_offset);

    graphic->setItemIndexMethod(QGraphicsScene::NoIndex);

    for (int i = 0; i < RowCount; ++i) {
        for (int j =0; j < RowCount; ++j) {
            BoardTile *board_tile = new BoardTile(board[i][j]);
            board_tile->setPos((corner_offset + j * 55), (corner_offset + i * 55));
            graphic->addItem(board_tile);
        }
    }
}

MainWindow::~MainWindow()
{
    delete ui;
    delete game;
}

void MainWindow::update_player() {
    int player_count = game->GetPlayerCount();
    if (player_count == 2) {
        ui->Score3->setStyleSheet(ui->Score3->styleSheet().append(QString("color: rgb(200, 200, 200);")));
        ui->Score3_text->setStyleSheet(ui->Score3_text->styleSheet().append(QString("color: rgb(200, 200, 200);")));
        ui->Score4->setStyleSheet(ui->Score4->styleSheet().append(QString("color: rgb(200, 200, 200);")));
        ui->Score4_text->setStyleSheet(ui->Score4_text->styleSheet().append(QString("color: rgb(200, 200, 200);")));
    } else if (player_count == 3) {
        ui->Score4->setStyleSheet(ui->Score4->styleSheet().append(QString("color: rgb(200, 200, 200);")));
        ui->Score4_text->setStyleSheet(ui->Score4_text->styleSheet().append(QString("color: rgb(200, 200, 200);")));
    }
}



void MainWindow::on_change_turn_button_clicked()
{
    // TODO ON TURN CHANGE
    // Read in data
    // do open cv crap on it
    // Spit out the vector of things

    // protoype

    vector<Tile> vec;
    Tile t1;
    Tile t2;
    Tile t3;
    Tile t4;

    int turn = game->GetTotalTurns();
    cout << "turn:" << turn << endl;
    if (turn == 0) {
        t1.col = 5;
        t1.row = 9;
        t1.letter = 'M';
        t1.isBlank = false;
        t2.col = 6;
        t2.row = 9;
        t2.letter = 'A';
        t2.isBlank = false;
        t3.col = 7;
        t3.row = 9;
        t3.letter = 'S';
        t3.isBlank = false;
        t4.col = 8;
        t4.row = 9;
        t4.letter = 'S';
        t4.isBlank = false;
    } else if (turn == 1) {
        t1.col = 5;
        t1.row = 10;
        t1.letter = 'S';
        t1.isBlank = false;
        t2.col = 5;
        t2.row = 8;
        t2.letter = 'A';
        t2.isBlank = true;
        t3.col = 5;
        t3.row = 7;
        t3.letter = 'C';
        t3.isBlank = true;
        t4.col = 5;
        t4.row = 6;
        t4.letter = 'K';
        t4.isBlank = false;
    } else if (turn == 2) {
        t1.col = 6;
        t1.row = 7;
        t1.letter = 'R';
        t1.isBlank = false;
        t2.col = 7;
        t2.row = 7;
        t2.letter = 'A';
        t2.isBlank = false;
        t3.col = 8;
        t3.row = 7;
        t3.letter = 'S';
        t3.isBlank = false;
        t4.col = 9;
        t4.row = 7;
        t4.letter = 'H';
        t4.isBlank = false;
    }
    if (turn == 0 || turn == 1 || turn == 2) {
        vec.push_back(t1);
        vec.push_back(t2);
        vec.push_back(t3);
        vec.push_back(t4);
        // Blank detection and asignment
        bool blank_there = false;
        for(int i = 0; i < vec.size(); i++) {
            Tile *tile = &vec[i];
            if (tile->isBlank) {
                BlankPopup blankPopup;
                blankPopup.setModal(true);
                blankPopup.exec();
                tile->letter = toupper(blankPopup.GetLetter());
                //TODO Way to highlight the cell under opperation, important if two blank used
            }
        }
        game->AddTiles(vec);
        game->PrintBoard();
    }

    // end protoype


    ui->Score1->setText(QString::number(game->GetPlayerScores().at(0)));
    ui->Score2->setText(QString::number(game->GetPlayerScores().at(1)));
    ui->Score3->setText(QString::number(game->GetPlayerScores().at(2)));
    ui->Score4->setText(QString::number(game->GetPlayerScores().at(3)));
    game->NextTurn();
    update_window();
    ui->scrabble_board->update(); // Something to update the scrabble_board (I don't think this works)
    ui->undo_button->setEnabled(1); // Enable undo button
}


void MainWindow::on_undo_button_clicked()
{
    game->UndoTurn();
    ui->undo_button->setEnabled(0); // Disable undo button (only works once each change turn)
}


void MainWindow::on_undo_button_2_clicked()
{
    //TODO add open cv calibration here
}

