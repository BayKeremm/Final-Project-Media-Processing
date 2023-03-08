#ifndef LEFTCOMMAND_H
#define LEFTCOMMAND_H

#include "commands/command.h"

class LeftCommand : public Command
{
public:
    LeftCommand(controllers &c, CommandFactory &factory);
    static std::unique_ptr<Command> construct(controllers &controller, CommandFactory &factory);
    void execute()override;
};

#endif // LEFTCOMMAND_H
