#include "custom_scene.h"
#include "game.h"

CustomScene::CustomScene(QWidget *parent)
    : QGraphicsScene(parent) {}

void CustomScene::mousePressEvent(QGraphicsSceneMouseEvent *event) {

  if (event->button() == Qt::LeftButton) {
    QPointF point = event->scenePos();
    int x = floor(point.x() / 32);
    int y = floor(point.y() / 32);
    emit tileClicked(QPoint(x, y));
  }
}

void CustomScene::keyPressEvent(QKeyEvent *event) {
//  std::cout << "keyboard event detected" << std::endl;
  if (event->key() == Qt::Key_Left || event->key() == Qt::Key_Right ||
      event->key() == Qt::Key_Up || event->key() == Qt::Key_Down) {
      emit keyPressed(event->key());
  }
}
