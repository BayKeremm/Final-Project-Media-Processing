#include "attack_nearest_enemy_command.h"
#include "goto_command.h"
#include "commands/command_factory.h"
#include <cmath>

AttackNearestEnemyCommand::AttackNearestEnemyCommand(controllers &c, CommandFactory &factory) : Command(c, factory)
{

}


void AttackNearestEnemyCommand::execute(){
    std::vector<std::unique_ptr<EnemyController>> &enemies = m_controllers.enemies;
    int x=0, y=0, cost=-1;

    for (std::unique_ptr<EnemyController> &enemyController : enemies){
        std::unique_ptr<Enemy> &enemy = enemyController->getModel();
        int tempCost = pow( m_player->getXPos()-enemy->getXPos() , 2);
        tempCost += pow( m_player->getYPos()-enemy->getYPos() , 2);
        if(!enemy->getDefeated()){
            if(cost ==-1 || tempCost<cost){
                cost = tempCost;
                x = enemy->getXPos();
                y = enemy->getYPos();
            }
            else if(tempCost< cost){
                cost = tempCost;
                x = enemy->getXPos();
                y = enemy->getYPos();
            }
        }
    }
    for (std::unique_ptr<PEnemyController> &enemyController : m_controllers.pEnemies){
        std::unique_ptr<Enemy> &enemy = enemyController->getModel();
        int tempCost = pow( m_player->getXPos()-enemy->getXPos() , 2);
        tempCost += pow( m_player->getYPos()-enemy->getYPos() , 2);
        if(!enemy->getDefeated()){
            if(cost ==-1 || tempCost<cost){
                cost = tempCost;
                x = enemy->getXPos();
                y = enemy->getYPos();
            }
            else if(tempCost< cost){
                cost = tempCost;
                x = enemy->getXPos();
                y = enemy->getYPos();
            }
        }
    }
    for (std::unique_ptr<XEnemyController> &enemyController : m_controllers.xEnemies){
        std::unique_ptr<Enemy> &enemy = enemyController->getModel();
        int tempCost = pow( m_player->getXPos()-enemy->getXPos() , 2);
        tempCost += pow( m_player->getYPos()-enemy->getYPos() , 2);
        if(!enemy->getDefeated()){
            if(cost ==-1 || tempCost<cost){
                cost = tempCost;
                x = enemy->getXPos();
                y = enemy->getYPos();
            }
            else if(tempCost< cost){
                cost = tempCost;
                x = enemy->getXPos();
                y = enemy->getYPos();
            }
        }
    }
    m_factory.createCommand("goto", {std::to_string(x), std::to_string(y)})->execute();
}


std::unique_ptr<Command> AttackNearestEnemyCommand::construct(controllers &controller, CommandFactory &factory){
    return std::make_unique<AttackNearestEnemyCommand>(controller, factory);
}
