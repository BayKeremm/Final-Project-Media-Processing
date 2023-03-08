#ifndef GRAPHICS_VIEW_H
#define GRAPHICS_VIEW_H

#include "mainwindow.h"

#include <QGraphicsView>
#include <QGraphicsScene>
#include <QGraphicsOpacityEffect>
#include <QPropertyAnimation>
#include <QGraphicsRectItem>
#include <QLabel>
#include <QKeyEvent>
#include <QObject>
#include <iostream>
#include <QList>
#include <QGraphicsPixmapItem>
#include <QPoint>
#include <QGraphicsSceneMouseEvent>
#include <QSlider>
#include <QDial>
#include <QScrollBar>

#include "controllers/controllers_struct.h"

#include "views/graphics/custom_view.h"
#include "views/graphics/custom_scene.h"

#include "views/graphics/energy_graphics_view.h"
#include "views/graphics/health_graphics_view.h"

using std::vector, std::unique_ptr;

class Game;
class QSlider;

class GraphicsView : public QObject
{
    Q_OBJECT
public:
    GraphicsView() = delete;

    GraphicsView(MainWindow *parent, Game *g,
             World *w, controllers_t *controllers);

    // Hides the graphics based view
    void hide();
    void show();

    void drawPastTile(int x, int y);
    QGraphicsRectItem * drawPoisonedTile(int x, int y);
    void erasePoisonedTile(int index);

    int getTileSize() const { return m_tileSize; };
    float getScaleValue() const { return m_scaleValue; };


public slots:
    void scaleChanged(float scale);
    void scaleViews(float scaleValue);

    void setEnergyView(int energy);
    void setHealthView(int health);
    void centerViewOnProtagonist(int x, int y);

private:
    Game * m_game;
    World * m_world;
    controllers_t * m_controllers;
    QGraphicsRectItem * m_square;

    // DRAW
    vector<std::map<int,QGraphicsRectItem *>> m_poisonedTiles;

    // graphics view variables
    int m_tileSize = 32;

    int prev_slider_value = 50;
    float m_scaleValue = 1.0;

    // heuristic
    float heuristicW = 0;
    float pathW = 0;

    unique_ptr<CustomView> m_gameView;
    unique_ptr<QGraphicsScene> m_gameScene;

    std::unique_ptr<QGraphicsView> m_mapView;
    std::unique_ptr<QGraphicsScene> m_mapScene;

    unique_ptr<QLabel> m_energyText;
    std::unique_ptr<EnergyGraphicsView> m_energyView;
    unique_ptr<QLabel> m_healthText;
    std::unique_ptr<HealthGraphicsView> m_healthView;
};

#endif // GRAPHICS_VIEW_H
