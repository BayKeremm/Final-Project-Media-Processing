#include "x_enemy_graphics_view.h"

XEnemyGraphicsView::XEnemyGraphicsView(QString image): EnemyGraphicsView(image)
{
    textValue->setDefaultTextColor(QColor("purple"));
}
