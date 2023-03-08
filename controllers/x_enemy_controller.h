#ifndef XENEMYCONTROLLER_H
#define XENEMYCONTROLLER_H

#include <QTimer>

#include "enemy_controller.h"
#include "world.h"

using std::unique_ptr;

class XEnemyController : public EnemyController  {
    Q_OBJECT
public:
  XEnemyController() = delete;
  XEnemyController(unique_ptr<Enemy> model);

  void setTileSize(int newTileSize) { m_tileSize = newTileSize; };

  void defeat() override;

  void move(int x, int y);

public slots:
  void setDefaultImage();

private:
  unique_ptr<QTimer> timer;

  int m_tileSize;
};

#endif // XENEMYCONTROLLER_H
