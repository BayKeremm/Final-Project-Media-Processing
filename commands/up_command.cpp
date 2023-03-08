#include "up_command.h"
#include "commands/command_factory.h"

#define DLOG(str)

UpCommand::UpCommand(controllers &c, CommandFactory &factory) : Command(c, factory)
{

}


void UpCommand::execute(){
    m_factory.createCommand("moveTo", {  std::to_string(m_player->getXPos()), std::to_string(m_player->getYPos() -1)})->execute();
}

std::unique_ptr<Command> UpCommand::construct(controllers &controller, CommandFactory &factory){
    return std::make_unique<UpCommand>(controller, factory);
}
