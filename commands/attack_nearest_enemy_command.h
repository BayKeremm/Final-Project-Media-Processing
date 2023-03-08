#ifndef ATTACKNEARESTENEMYCOMMAND_H
#define ATTACKNEARESTENEMYCOMMAND_H

#include "command.h"

class AttackNearestEnemyCommand : public Command
{
public:
    AttackNearestEnemyCommand(controllers &c, CommandFactory &factory);
    void execute()override;
    static std::unique_ptr<Command> construct(controllers &controller, CommandFactory &factory);
};

#endif // ATTACKNEARESTENEMYCOMMAND_H
