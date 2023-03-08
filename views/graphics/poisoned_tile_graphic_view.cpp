#include "poisoned_tile_graphic_view.h"

PoisonedTileGraphicView::PoisonedTileGraphicView()
{
    //set graphic
    setPixmap(QPixmap(":/images/poison_tile.png"));
}

void PoisonedTileGraphicView::erasePoisonTile()
{
    delete this;
}
