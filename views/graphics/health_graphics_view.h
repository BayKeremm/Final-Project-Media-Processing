#ifndef HEALTHGRAPHICSVIEW_H
#define HEALTHGRAPHICSVIEW_H

#include "mainwindow.h"

#include <QProgressBar>

class HealthGraphicsView : public QProgressBar
{
public:
    HealthGraphicsView(MainWindow * parent = 0);
    ~HealthGraphicsView() = default;

protected:
    void paintEvent(QPaintEvent *);

private:
    void draw(QPainter *painter, QRect rect, int w);
    void drawEllipticalRectangle(QPainter *painter, QRect rect, int w);

};

#endif // HEALTHGRAPHICSVIEW_H
