#include "commands/command.h"
#include "controllers/controllers_struct.h"

Command::Command(controllers &controller, CommandFactory &factory) : m_controllers{controller}, m_player{m_controllers.protagonist->getModel()}, m_factory{factory} {

}

void Command::execute(){

}

std::vector<std::string> Command::getAvailableCommands(){
    return m_availableCommands;
}

std::unique_ptr<Command> Command::construct(controllers &controller, CommandFactory &factory){
    return std::make_unique<Command>(controller, factory);
}
