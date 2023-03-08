#ifndef HELPCOMMAND_H
#define HELPCOMMAND_H
#include "commands/command.h"

class HelpCommand : public Command
{
public:
    HelpCommand(controllers &c, CommandFactory &factory);
    static std::unique_ptr<Command> construct(controllers &controller, CommandFactory &factory);
    void execute()override;
};

#endif // HELPCOMMAND_H
