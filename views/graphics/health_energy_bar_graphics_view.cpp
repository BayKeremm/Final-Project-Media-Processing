#include "health_energy_bar_graphics_view.h"


HealthEnergyBarGraphicsView::HealthEnergyBarGraphicsView(QWidget *parent) :
    QGraphicsView(parent), m_overlayScene(NULL) {}

HealthEnergyBarGraphicsView::HealthEnergyBarGraphicsView(QGraphicsScene *scene, QWidget *parent) :
    QGraphicsView(scene, parent), m_overlayScene(NULL) {}

void HealthEnergyBarGraphicsView::setOverlayScene(QGraphicsScene *scene) {
    if (scene == m_overlayScene) return;
    m_overlayScene = scene;
    connect(scene, SIGNAL(changed(QList<QRectF>)), SLOT(overlayChanged()));
    update();
}

void HealthEnergyBarGraphicsView::paintEvent(QPaintEvent *ev) {
    QGraphicsView::paintEvent(ev);
    if (m_overlayScene) paintOverlay();
}

void HealthEnergyBarGraphicsView::paintOverlay() {
    QPainter p(viewport());
    p.setRenderHints(renderHints());
    m_overlayScene->render(&p, viewport()->rect());
}
