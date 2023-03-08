#include "moveto_command.h"
#include "commands/command_factory.h"
#include "game.h"

#define DLOG(str)


MovetoCommand::MovetoCommand(controllers &c, CommandFactory &factory, int x, int y, Game &g): Command(c, factory),
    m_x{x},
    m_y{y},
    m_game{g},
    m_difficultyFactor{m_game.getDifficultyfactor()}
{
}



void MovetoCommand::execute(){
    if ((m_x >= 0) && (m_x <= m_game.getWorldWidth() - 1) && (m_y >= 0) &&
        (m_y <= m_game.getWorldHeight() - 1)) {
        int dmgTaken =0;

      std::vector<std::unique_ptr<Tile>> &tiles = m_game.getTiles();
      std::unique_ptr<Protagonist> &protagonistModel = m_controllers.protagonist->getModel();

      int index = m_x + m_y * m_game.getWorldWidth();
      float tileValue = tiles[index]->getValue();
      // check if tile is passable
      if (tileValue != std::numeric_limits<float>::max()) {

        // check for collisions
        bool collision = false;

        // hpack collision <-- DONE
        for (std::unique_ptr<HealthpackController> &hpackC : m_controllers.hPacks) {
          std::unique_ptr<Tile> &hpack = hpackC->getModel();
          if (hpack->getXPos() == m_x && hpack->getYPos() == m_y) {
            collision = true;
            if (!hpackC->isEmpty()) {

              DLOG("Player healed by: " << hpack->getValue() / m_difficultyFactor);

              // heal protagonist
              m_controllers.protagonist->heal(hpack->getValue() /m_difficultyFactor);

              // use healthpack
              hpackC->used();

              // make impassable
              tiles[index]->setValue(std::numeric_limits<float>::max());
              m_controllers.astar->updateFlag(tiles[index]->getXPos(), tiles[index]->getYPos(), 4);
            }
          }
        }

        // enemy collision <-- DONE
        for (std::unique_ptr<EnemyController> &enemyC : m_controllers.enemies) {
          std::unique_ptr<Enemy> &enemy = enemyC->getModel();
          if (enemy->getXPos() == m_x && enemy->getYPos() == m_y) {
            collision = true;
            if (!enemy->getDefeated()) {

              DLOG("Collision with enemy ! Strength: " << enemy->getValue() /m_difficultyFactor);

              // fight
              dmgTaken = enemy->getValue()/m_difficultyFactor;
              enemyC->defeat();
              // make impassable
              tiles[index]->setValue(std::numeric_limits<float>::max());
              m_controllers.astar->updateFlag(enemy->getXPos(), enemy->getYPos(), 4);
            }
          }
        }

        // pEnemy collision <-- DONE
        for (std::unique_ptr<PEnemyController> &pEnemyC : m_controllers.pEnemies) {
          //        std::unique_ptr<Enemy> &pEnemy = pEnemyC->getModel();
          PEnemy &pEnemy = static_cast<PEnemy &>(*pEnemyC->getModel());
          if (pEnemy.getXPos() == m_x && pEnemy.getYPos() == m_y) {
            collision = true;
            if (!pEnemy.getDefeated()) {

              DLOG("Collision with poisoned enemy ! Strength: "
                   << pEnemy.getValue() / m_difficultyFactor);

              // fight
              dmgTaken = pEnemy.getValue()/m_difficultyFactor;
              // if protagist wins
              pEnemyC->defeat();
              // poison effect
              pEnemy.poison();
              // poison surrounding tiles
              int px = rand() % 2 + 1;
              int py = rand() % 2 + 1;
              for (int i = -px; i < px + 1; i++) {
                for (int j = -py; j < py + 1; j++) {
                    // draw poisoned tiles
                    m_game.drawPoisonnedTile(m_x +i, m_y+j, pEnemy);
                }
              }
              // make impassable
              tiles[index]->setValue(std::numeric_limits<float>::max());
              m_controllers.astar->updateFlag(pEnemy.getXPos(), pEnemy.getYPos(), 4);
            }
          }
        }

        // xEnemy collision <-- DONE
        for (std::unique_ptr<XEnemyController> &xEnemyC : m_controllers.xEnemies) {
          std::unique_ptr<Enemy> &enemy = xEnemyC->getModel();
          if (enemy->getXPos() == m_x && enemy->getYPos() == m_y) {
            collision = true;
            if (!enemy->getDefeated()) {
              DLOG("Collision with moving enemy ! Strength: "
                   << enemy->getValue() / m_difficultyFactor);
              // fight
              dmgTaken = enemy->getValue()/m_difficultyFactor;
              // set enemy controller to defeated
              xEnemyC->defeat();
              // make impassable
              tiles[index]->setValue(std::numeric_limits<float>::max());
              m_controllers.astar->updateFlag(enemy->getXPos(), enemy->getYPos(), 4);
            }
          }
        }

        // if no collision then move to tile
        if (!collision) {

          m_game.drawPastTile(protagonistModel->getXPos(), protagonistModel->getYPos());
          // move protagonist
          m_controllers.protagonist->moveTo(m_x, m_y);

          // DLOG("Protagonist position:  x:" << x << "  y: " << y);

          // lose energy
          m_controllers.protagonist->loseEnergy(1.f - tileValue * m_difficultyFactor / 2);

          // draw fading square behind in path
        }

      } else {
        std::cout << "You hit an impassable tile !" << std::endl;
      }
      if(dmgTaken>0)m_controllers.protagonist->fight(dmgTaken);
    }
}


std::unique_ptr<Command> MovetoCommand::construct(controllers &c, CommandFactory &factory, int x, int y, Game &g){
    return std::make_unique<MovetoCommand>(c, factory, x, y, g);
}
