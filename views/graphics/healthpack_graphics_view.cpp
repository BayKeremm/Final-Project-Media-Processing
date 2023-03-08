#include "healthpack_graphics_view.h"

HealthpackGraphicsView::HealthpackGraphicsView(QString image) : TileGraphicView(image)
{
    textValue->setDefaultTextColor(QColor("blue"));
}
