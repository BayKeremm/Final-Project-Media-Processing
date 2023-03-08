#ifndef COMMAND_H_
#define COMMAND_H_

#include "controllers/controllers_struct.h"
#include "views/view.h"

class CommandFactory;
class Command{
protected:
    controllers &m_controllers;
    std::vector<std::string> m_availableCommands = {"up", "down", "left", "right", "help", "goto x y", "attackNearestEnemy", "takeNearestHealthpack"};
    std::unique_ptr<Protagonist> &m_player;
    CommandFactory &m_factory;
public:
    Command(controllers &controller, CommandFactory &factory);
    virtual void execute();
    static std::unique_ptr<Command> construct(controllers &controller, CommandFactory &factory);
    std::vector<std::string> getAvailableCommands();
};



#endif //COMMAND_H_
