#ifndef TAKENEARESTHEALTHPACKCOMMAND_H
#define TAKENEARESTHEALTHPACKCOMMAND_H

#include "command.h"

class TakeNearestHealthpackCommand : public Command
{
public:
    TakeNearestHealthpackCommand(controllers &c, CommandFactory &factory);
    static std::unique_ptr<Command> construct(controllers &controller, CommandFactory &factory);
    void execute()override;
};

#endif // TAKENEARESTHEALTHPACKCOMMAND_H
