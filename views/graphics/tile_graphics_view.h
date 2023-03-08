#ifndef TILE_GRAPHICS_VIEW_H
#define TILE_GRAPHICS_VIEW_H

#include <QGraphicsPixmapItem>
#include <QGraphicsItem>

using std::unique_ptr;

class TileGraphicView: public QGraphicsPixmapItem {

public:
    TileGraphicView(QString image);

    unique_ptr<QGraphicsTextItem> &getTextValue() {return textValue;};
    void defineTextValue(int newValue);
    void setTextValue(int newValue) { textValue->setPlainText(QString::number(newValue)); }

protected:
    unique_ptr<QGraphicsTextItem> textValue;
};

#endif // TILE_GRAPHICS_VIEW_H
