#ifndef COMMANDFACTORY_H
#define COMMANDFACTORY_H

#include <map>
#include "commands/commands.h"

class Game;
class CommandFactory
{
private:
    controllers m_controllers;
    Game &m_game;

    std::map<std::string,  std::unique_ptr<Command>(*)(controllers&, CommandFactory &factory)> m_standardBuilders={
        {"help", HelpCommand::construct},
        {"up", UpCommand::construct},
        {"left", LeftCommand::construct},
        {"attackNearestEnemy", AttackNearestEnemyCommand::construct},
        {"takeNearestHealthpack", TakeNearestHealthpackCommand::construct}
    };

    std::vector<std::string> m_nonStandardBuilders = {"right", "down", "goto", "moveTo", "print"};

public:
    CommandFactory(controllers c, Game &game);
    std::unique_ptr<Command> createCommand(std::string command, std::vector<std::string> args);
    std::vector<std::string> getCommands();
};

#endif // COMMANDFACTORY_H
