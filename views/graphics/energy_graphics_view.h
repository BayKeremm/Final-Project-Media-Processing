#ifndef ENERGYGRAPHICSVIEW_H
#define ENERGYGRAPHICSVIEW_H

#include "mainwindow.h"

#include <QProgressBar>

class EnergyGraphicsView : public QProgressBar
{
public:
    EnergyGraphicsView(MainWindow * parent = 0);
    ~EnergyGraphicsView() = default;


protected:
    void paintEvent(QPaintEvent *);

private:
    void draw(QPainter *painter, QRect rect, int w);
    void drawEllipticalRectangle(QPainter *painter, QRect rect, int w);

};

#endif // ENERGYGRAPHICSVIEW_H
