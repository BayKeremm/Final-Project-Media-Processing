#include "down_command.h"
#include "commands/command_factory.h"

DownCommand::DownCommand(controllers &c, CommandFactory &factory, int maxHeight) : Command(c, factory), m_maxHeight{maxHeight}
{

}

void DownCommand::execute(){
    m_factory.createCommand("moveTo", {std::to_string(m_player->getXPos()), std::to_string(m_player->getYPos()+1)})->execute();
}

std::unique_ptr<Command> DownCommand::construct(controllers &controller, CommandFactory &factory, int maxHeight){
    return std::make_unique<DownCommand>(controller, factory, maxHeight);
}
