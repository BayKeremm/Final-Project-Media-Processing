#include "take_nearest_healthpack_command.h"
#include "commands/goto_command.h"

#include <cmath>
#include "commands/command_factory.h"


TakeNearestHealthpackCommand::TakeNearestHealthpackCommand(controllers &c, CommandFactory &factory): Command(c, factory)
{

}


void TakeNearestHealthpackCommand::execute(){
    std::vector<std::unique_ptr<HealthpackController>> &hPacks = m_controllers.hPacks;
    int x=0, y=0, cost=-1;

    for (std::unique_ptr<HealthpackController> &hPackController : hPacks){
        std::unique_ptr<Tile> &hPack = hPackController->getModel();
        int tempCost = pow( m_player->getXPos()-hPack->getXPos() , 2);
        tempCost += pow( m_player->getYPos()-hPack->getYPos() , 2);
        if(!hPackController->isEmpty()){
            if(cost ==-1 || tempCost<cost){
                cost = tempCost;
                x = hPack->getXPos();
                y = hPack->getYPos();
            }
            else if(tempCost< cost){
                cost = tempCost;
                x = hPack->getXPos();
                y = hPack->getYPos();
            }
        }
    }
    m_factory.createCommand("goto", {std::to_string(x), std::to_string(y)})->execute();
}


std::unique_ptr<Command> TakeNearestHealthpackCommand::construct(controllers &controller, CommandFactory &factory){
    return std::make_unique<TakeNearestHealthpackCommand>(controller, factory);
}
