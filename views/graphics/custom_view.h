#ifndef CUSTOMVIEW_H
#define CUSTOMVIEW_H

#include <QObject>
#include <QGraphicsView>
#include <QWheelEvent>

class Game;

class CustomView : public QGraphicsView {
    Q_OBJECT
public:
  CustomView(QWidget * parent);

  void wheelEvent(QWheelEvent *event);

};

#endif // CUSTOMVIEW_H
