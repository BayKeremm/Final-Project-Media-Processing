#ifndef CONTROLLERS_STRUCT_H
#define CONTROLLERS_STRUCT_H

#include "controllers/enemy_controller.h"
#include "controllers/healthpack_controller.h"
#include "controllers/p_enemy_controller.h"
#include "controllers/protagonist_controller.h"
#include "controllers/x_enemy_controller.h"
#include "pathfinder/astar.h"
#include "controllers/poisened_tile_struct.h"

using std::vector, std::unique_ptr;

class ProtagonistController;

typedef struct controllers{
    vector<unique_ptr<EnemyController>> &enemies;
    vector<unique_ptr<PEnemyController>> &pEnemies;
    vector<unique_ptr<XEnemyController>> &xEnemies;
    vector<unique_ptr<HealthpackController>> &hPacks;
    unique_ptr<ProtagonistController> &protagonist;
    unique_ptr<Astar> &astar;
    vector<poisened_tile_t> &poisonedTiles;
}controllers_t;

#endif // CONTROLLERS_STRUCT_H
