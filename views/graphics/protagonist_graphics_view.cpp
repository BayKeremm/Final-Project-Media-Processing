#include "protagonist_graphics_view.h"
#include <QKeyEvent>
#include <iostream>

ProtagonistGraphicsView::ProtagonistGraphicsView(QString image) : TileGraphicView(image)
{
    // dont show textValue for protagonist
    textValue->hide();
    // make protagonistView focusable
    setFlag(QGraphicsItem::ItemIsFocusable);
    // set protagonistView to current focus
    setFocus();
    // set it above all else
    setZValue(2);
}
