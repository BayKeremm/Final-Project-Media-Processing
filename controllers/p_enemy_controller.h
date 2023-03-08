#ifndef P_ENEMY_CONTROLLER_H
#define P_ENEMY_CONTROLLER_H

#include "enemy_controller.h"
#include "world.h"

using std::unique_ptr;

class PEnemyController : public EnemyController {
    Q_OBJECT
public:
  PEnemyController() = delete;
  PEnemyController(unique_ptr<Enemy> model);

  void defeat() override;
  bool isDying() { return dying; };

private:
  bool dying = false;
};

#endif // P_ENEMY_CONTROLLER_H
