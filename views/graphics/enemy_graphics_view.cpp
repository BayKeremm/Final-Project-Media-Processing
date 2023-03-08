#include "enemy_graphics_view.h"

EnemyGraphicsView::EnemyGraphicsView(QString image) : TileGraphicView(image)
{
    textValue->setDefaultTextColor(QColor("red"));
}

