#include "help_command.h"
#include "commands/command_factory.h"

HelpCommand::HelpCommand(controllers &c, CommandFactory &factory) : Command(c, factory)
{

}

void HelpCommand::execute(){
    std::string cmds;
    for(std::string command : m_availableCommands){
        cmds += command+"\n";
    }
    m_factory.createCommand("print", {cmds})->execute();
}

std::unique_ptr<Command> HelpCommand::construct(controllers &controller, CommandFactory &factory){
    return std::make_unique<HelpCommand>(controller, factory);
}
