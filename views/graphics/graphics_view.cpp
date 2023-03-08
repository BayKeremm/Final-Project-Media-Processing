#include "graphics_view.h"

#include "game.h"

#include <QSlider>
#include <QDial>
#include <QScrollBar>
#include <QPushButton>

GraphicsView::GraphicsView(MainWindow *parent, Game *g, World *w,
                           controllers_t *controllers)
    : m_game{g}, m_world{w}, m_controllers{controllers} {

#define DEBUG
#ifdef DEBUG
#include <iostream>
#define DLOG(str) std::cout << "[gView] " << str << std::endl;
#else
#define DLOG(str)
#endif
  m_mapView = std::make_unique<QGraphicsView>(parent);
  m_mapView->setGeometry(10, 40, 20 * m_tileSize, 20 * m_tileSize);
  // initialize view
  m_gameView = std::make_unique<CustomView>(parent);
  m_gameView->setGeometry(10, 40, 20 * m_tileSize, 20 * m_tileSize);

  m_gameView->setStyleSheet("background:transparent");

  // define scene
  m_gameScene = std::make_unique<CustomScene>(parent);
  m_gameScene->setSceneRect(0, 0, m_world->getCols() * m_tileSize,
                            m_world->getCols() * m_tileSize);

  // connect mouse to game
  connect(m_gameScene.get(), SIGNAL(tileClicked(QPoint)), m_game,
          SLOT(pathToPoint(QPoint)));
  // connect key press to game
  connect(m_gameScene.get(), SIGNAL(keyPressed(int)), m_game, SLOT(setKey(int)));

  m_mapScene = std::make_unique<QGraphicsScene>(parent);
  m_mapScene->setSceneRect(0, 0, m_world->getCols(), m_world->getCols());

  m_mapView->setScene(m_mapScene.get());
  // set view starting at 0,0 (where protagonist starts)
  m_mapView->centerOn(0, 0);
  m_mapView->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
  m_mapView->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
  m_mapView->show();

  // SHOW MAP IN BACKGROUND
  QPixmap map(m_game->getFileName());
  m_mapScene->addPixmap(map);
  m_mapView->scale(m_tileSize, m_tileSize);

  // add special tiles to the scene
  int x;
  int y;
  // give tilesize to controller
  m_controllers->protagonist->setTileSize(m_tileSize);
  // add protagonist to the scene
  x = m_controllers->protagonist->getModel()->getXPos() * m_tileSize;
  y = m_controllers->protagonist->getModel()->getYPos() * m_tileSize;
  m_controllers->protagonist->getView()->setPos(x, y);
  m_gameScene->addItem(
      m_controllers->protagonist->getView().get()); // Reason of the segfault ?

  // add enemies to the scene
  for (auto &enemyController : m_controllers->enemies) {
    // DLOG("Enemy controller")
    x = enemyController->getModel()->getXPos() * m_tileSize;
    y = enemyController->getModel()->getYPos() * m_tileSize;
    enemyController->getView()->setPos(x, y);
    enemyController->getView()->defineTextValue(enemyController->getModel()->getValue()/m_game->getDifficultyfactor());
    m_gameScene->addItem(enemyController->getView().get());
    m_gameScene->addItem(enemyController->getView()->getTextValue().get());
  }
  // add p_enemies to the scene
  for (auto &pEnemyController : m_controllers->pEnemies) {
    // DLOG("pEnemy controller")
    x = pEnemyController->getModel()->getXPos() * m_tileSize;
    y = pEnemyController->getModel()->getYPos() * m_tileSize;
    pEnemyController->getView()->setPos(x, y);
    pEnemyController->getView()->defineTextValue(pEnemyController->getModel()->getValue()/m_game->getDifficultyfactor());
    m_gameScene->addItem(pEnemyController->getView().get());
    m_gameScene->addItem(pEnemyController->getView()->getTextValue().get());
  }
  // add xEnemies to the scene
  for (auto &xEnemyController : m_controllers->xEnemies) {
    // give tilesize to controller
    xEnemyController->setTileSize(m_tileSize);
    DLOG("XEnemy controller")
    x = xEnemyController->getModel()->getXPos() * m_tileSize;
    y = xEnemyController->getModel()->getYPos() * m_tileSize;
    xEnemyController->getView()->setPos(x, y);
    xEnemyController->getView()->defineTextValue(xEnemyController->getModel()->getValue()/m_game->getDifficultyfactor());
    m_gameScene->addItem(xEnemyController->getView().get());
    m_gameScene->addItem(xEnemyController->getView()->getTextValue().get());
  }
  // add healthpacks to the scene
  for (auto &healthpackController : m_controllers->hPacks) {
    // DLOG("hPack controller")
    x = healthpackController->getModel()->getXPos() * m_tileSize;
    y = healthpackController->getModel()->getYPos() * m_tileSize;
    healthpackController->getView()->setPos(x, y);
    healthpackController->getView()->defineTextValue(healthpackController->getModel()->getValue()/m_game->getDifficultyfactor());
    m_gameScene->addItem(healthpackController->getView().get());
    m_gameScene->addItem(healthpackController->getView()->getTextValue().get());
  }

  // set scene to the view and show
  m_gameView->setScene(m_gameScene.get());
  m_gameView->show();
  // set view starting at 0,0 (where protagonist starts)
    m_gameView->centerOn(0, 0);

  m_gameView->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
  m_gameView->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

  // define energy text
  m_energyText = std::make_unique<QLabel>(parent);
  m_energyText->setText("ENERGY:"); // define energy text
  m_energyText->setFont(QFont("roboto", 10));
  m_energyText->move(10, 10);
  // define energy bar
  m_energyView = std::make_unique<EnergyGraphicsView>(parent);
  m_energyView->setValue(m_controllers->protagonist->getModel()->getEnergy());
  // connect energy view to protagonist
  connect(controllers->protagonist->getModel().get(),
          SIGNAL(energyChanged(int)), this, SLOT(setEnergyView(int)));

  // define health text
  m_healthText = std::make_unique<QLabel>(parent);
  m_healthText->setText("HEALTH:"); // define energy text
  m_healthText->setFont(QFont("roboto", 10));
  m_healthText->move(300, 10);
  // define health bar
  m_healthView = std::make_unique<HealthGraphicsView>(parent);
  m_healthView->setValue(m_controllers->protagonist->getModel()->getHealth());
  // connect health view to protagonist
  connect(controllers->protagonist->getModel().get(),
          SIGNAL(healthChanged(int)), this, SLOT(setHealthView(int)));

  // size MainWindow to fit all TODO SET UNIVERSAL A PRIORI
  parent->setFixedSize(m_gameView->width() + 200,
                       m_gameView->height() + m_energyView->height() + 20);

  // connect protagonist to center of view
  connect(controllers->protagonist->getModel().get(),
          SIGNAL(posChanged(int,int)), this,
          SLOT(centerViewOnProtagonist(int,int)));
}

void GraphicsView::hide() {
  m_gameView->hide();
  m_mapView->hide();
  m_energyText->hide();
  m_energyView->hide();
  m_healthText->hide();
  m_healthView->hide();
}

void GraphicsView::show() {
  m_gameView->show();
  m_mapView->show();
  //m_path_text->show();
  m_energyText->show();
  m_energyView->show();
  m_healthText->show();
  m_healthView->show();
  //m_heuristicSlider->show();
  m_gameView->setFocus();
}

void GraphicsView::drawPastTile(int x, int y) {
  QGraphicsRectItem *m_square =
      new QGraphicsRectItem(x * m_tileSize, y * m_tileSize, m_tileSize,
                            m_tileSize); // create square with size 50x50
  m_square->setBrush(QBrush(Qt::black)); // set initial brush color to black
  QGraphicsOpacityEffect *eff = new QGraphicsOpacityEffect(this);
  m_square->setGraphicsEffect(eff);
  QPropertyAnimation *animation = new QPropertyAnimation(eff, "opacity");
  animation->setDuration(1000); // Set the duration to 1 second
  animation->setStartValue(1);  // Set the starting value to fully opaque
  animation->setEndValue(0);    // Set the ending value to fully transparent
  animation->start(QPropertyAnimation::DeleteWhenStopped);
  m_gameScene->addItem(m_square); // add square to the scene
}

QGraphicsRectItem *GraphicsView::drawPoisonedTile(int x, int y) {
  // draw the square
  QGraphicsRectItem *m_square =
      new QGraphicsRectItem(x * m_tileSize, y * m_tileSize, m_tileSize,
                            m_tileSize); // create square with size 50x50
  m_square->setBrush(QBrush(Qt::green)); // set initial brush color to black

  // add square to the scene
  m_gameScene->addItem(m_square);

  return m_square;
}

void GraphicsView::centerViewOnProtagonist(int x, int y) {
  m_gameView->centerOn(x * m_tileSize, y * m_tileSize);
  m_mapView->centerOn(x, y);
}

void GraphicsView::setEnergyView(int energy) { m_energyView->setValue(energy); }

void GraphicsView::setHealthView(int health) { m_healthView->setValue(health); }

void GraphicsView::scaleViews(float scaleValue) {
  m_gameView->setTransformationAnchor(QGraphicsView::AnchorViewCenter);
  m_gameView->scale(scaleValue, scaleValue);
  m_mapView->setTransformationAnchor(QGraphicsView::AnchorViewCenter);
  m_mapView->scale(scaleValue, scaleValue);
}

//float GraphicsView::getHeuristicWeight()
//{
//    return heuristicW;
//}
//
//float GraphicsView::getPathWeight()
//{
//    return pathW;
//}

void GraphicsView::scaleChanged(float newScale){
    int diff = prev_slider_value-newScale;
    prev_slider_value = newScale;
    std::cout << diff << std::endl;
    if(diff > 0){
        scaleViews(0.5);
    }else{
        scaleViews(2);
    }
}

//void GraphicsView::heuristicChanged(float newHeuristic)
//{
//    std::cout << newHeuristic/10 << std::endl;
//    heuristicW = newHeuristic/10;
//}

//void GraphicsView::pathWeightChanged(float newPathWeight)
//{
//    pathW = newPathWeight;
//}
