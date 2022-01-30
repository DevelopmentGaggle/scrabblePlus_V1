#ifndef TILE_H
#define TILE_H

#include <QGraphicsItem>
#include "Game.h"

class BoardTile : public QGraphicsPixmapItem
{
public:
    BoardTile(Tile &tile);

    void update();

private:
    Tile tile;
};

#endif // TILE_H
