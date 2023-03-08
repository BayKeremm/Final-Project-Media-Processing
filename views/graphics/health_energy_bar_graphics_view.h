#ifndef HEALTHENERGYBARGRAPHICSVIEW_H
#define HEALTHENERGYBARGRAPHICSVIEW_H

#ifdef WIN32
    #include "qtmetamacros.h"
#endif
#include <QGraphicsView>
#include <QGraphicsScene>
#include <QEvent>


class HealthEnergyBarGraphicsView : public QGraphicsView
{
    Q_OBJECT

    //https://stackoverflow.com/questions/18411250/draw-an-item-in-a-static-location-relative-to-the-qgraphicsview

    QGraphicsScene * m_overlayScene;
public:
    explicit HealthEnergyBarGraphicsView(QWidget* parent = 0);

    explicit HealthEnergyBarGraphicsView(QGraphicsScene * scene = 0, QWidget * parent = 0);

    void setOverlayScene(QGraphicsScene * scene);

    QGraphicsScene * overlayScene() const { return m_overlayScene; }

    void paintEvent(QPaintEvent *ev);

    virtual void paintOverlay();

    Q_SLOT void overlayChanged() { update(); }
};

#endif // HEALTHENERGYBARGRAPHICSVIEW_H
