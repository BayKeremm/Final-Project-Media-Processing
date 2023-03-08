#include "custom_view.h"
#include "game.h"

CustomView::CustomView(QWidget *parent)
    : QGraphicsView(parent) {}

void CustomView::wheelEvent(QWheelEvent *event)
{
    return;
}
