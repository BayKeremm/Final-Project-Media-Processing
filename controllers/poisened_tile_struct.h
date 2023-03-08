#ifndef POISENED_TILE_STRUCT_H
#define POISENED_TILE_STRUCT_H

#include "qgraphicsitem.h"
#include "world.h"
#include <memory>

using std::unique_ptr;

typedef struct poisened_tile_t{
    int index_t;
    PEnemy *pEnemy_t;
    QGraphicsRectItem *poisonedSquare_t;
    bool active_t;
}poisened_tile_t;

#endif // POISENED_TILE_STRUCT_H
