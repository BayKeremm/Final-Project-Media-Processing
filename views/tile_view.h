#ifndef TILE_VIEW_H
#define TILE_VIEW_H

#include "qgraphicsitem.h"
#include "qgraphicsscene.h"
#include <vector>

using namespace std;

class TileView : public QGraphicsRectItem
{
public:
    TileView();

    void draw(QGraphicsScene *scene);
};

#endif // TILE_VIEW_H
