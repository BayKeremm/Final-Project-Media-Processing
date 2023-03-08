#include "p_enemy_graphics_view.h"

PEnemyGraphicsView::PEnemyGraphicsView(QString image): EnemyGraphicsView(image)
{
    textValue->setDefaultTextColor(QColor("green"));
}
