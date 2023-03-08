#include "left_command.h"
#include "commands/command_factory.h"

LeftCommand::LeftCommand(controllers &c, CommandFactory &factory) : Command(c, factory){

}

void LeftCommand::execute(){
    m_factory.createCommand("moveTo", {std::to_string(m_player->getXPos()-1), std::to_string(m_player->getYPos())})->execute();
}


std::unique_ptr<Command> LeftCommand::construct(controllers &controller, CommandFactory &factory){
    return std::make_unique<LeftCommand>(controller, factory);
}
