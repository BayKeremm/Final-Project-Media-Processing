#include "tile_graphics_view.h"
#include "qfont.h"

TileGraphicView::TileGraphicView(QString image) {
    //set graphic
    setPixmap(QPixmap(image));
    setZValue(1);
    // set textValue
    textValue = std::make_unique<QGraphicsTextItem>("Value");
}


void TileGraphicView::defineTextValue(int newValue)
{
    textValue->setZValue(3);
    textValue->setFont(QFont("roboto", 11, QFont::Bold));
    textValue->setPlainText(QString::number(newValue));
    QPointF p = this->pos();
    textValue->setPos(p.x(),p.y()-20);
}
