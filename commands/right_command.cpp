#include "right_command.h"
#include "commands/command_factory.h"

RightCommand::RightCommand(controllers &c, CommandFactory &factory, int maxWidth) : Command(c, factory), m_maxWidth{maxWidth}
{

}


void RightCommand::execute(){
    m_factory.createCommand("moveTo", {std::to_string(m_player->getXPos()+1), std::to_string(m_player->getYPos())} )->execute();
}


std::unique_ptr<Command> RightCommand::construct(controllers &controller, CommandFactory &factory, int maxWidth){
    return std::make_unique<RightCommand>(controller, factory, maxWidth);
}
