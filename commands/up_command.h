#ifndef UPCOMMAND_H
#define UPCOMMAND_H
#include "commands/command.h"


class UpCommand : public Command
{
public:
    UpCommand(controllers &c, CommandFactory &factory);
    static std::unique_ptr<Command> construct(controllers &controller, CommandFactory &factory);
    void execute() override;
};

#endif // UPCOMMAND_H
