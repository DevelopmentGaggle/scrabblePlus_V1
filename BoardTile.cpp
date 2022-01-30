#include "BoardTile.h"
#include "Game.h"

#include <QGraphicsScene>
#include <QPainter>
#include <QRandomGenerator>
#include <QStyleOption>
#include <QtMath>

#include <iostream>
using namespace std;

BoardTile::BoardTile(Tile &tile): QGraphicsPixmapItem(QPixmap(":/Resources/BoardAttributes/tile.png"))
{
    this->tile = tile;

    this->setTransformationMode(Qt::SmoothTransformation);

    update();
}

void BoardTile::update() {
    Multiplier multiplier = tile.multiplier;
    char letter = tile.letter;
    bool isBlank = tile.isBlank;
    QPixmap tile_image;

    if (letter == '-') { // If there is no letter, show what is below the letter
        if (multiplier != NN) {
            if (multiplier == DL) {
                tile_image = QPixmap(":/Resources/BoardAttributes/DL.png");
            }
            else if (multiplier == TL) {
                tile_image = QPixmap(":/Resources/BoardAttributes/TL.png");
            }
            else if (multiplier == DW) {
                tile_image = QPixmap(":/Resources/BoardAttributes/DW.png");
            }
            else {
                tile_image = QPixmap(":/Resources/BoardAttributes/TW.png");
            }
        } else {
            tile_image = QPixmap(":/Resources/BoardAttributes/tile.png");
        }
    } else { // If there is a letter, show the letter tile
        //if (isBlank) { // If it is a blank tile, do this
            //TODOD Fancy implementation? (make it so that it has a small letter in the corner)
        //    tile_image = QPixmap(":/Resources/Letters/BB.png");
        //} else { // If it is a normal tile, do this (file based on letter)
            QString resFile = ":/Resources/Letters/";
            resFile += letter;
            tile_image = QPixmap(resFile);
        //}
    }
    this->setPixmap(tile_image);
}
