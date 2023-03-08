#ifndef CUSTOMSCENE_H
#define CUSTOMSCENE_H

#include <QObject>
#include <QGraphicsScene>
#include <QGraphicsSceneMouseEvent>
#include <QKeyEvent>

class Game;

class CustomScene : public QGraphicsScene {
  Q_OBJECT
public:
  CustomScene(QWidget *parent);

protected:
  void mousePressEvent(QGraphicsSceneMouseEvent *event);
  void keyPressEvent(QKeyEvent *event);

signals:
  void tileClicked(QPoint point);
  void keyPressed(int key);
};

#endif // CUSTOMSCENE_H
