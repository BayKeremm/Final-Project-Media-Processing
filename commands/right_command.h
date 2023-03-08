#ifndef RIGHTCOMMAND_H
#define RIGHTCOMMAND_H

#include "commands/command.h"

class RightCommand : public Command
{
private:
    int m_maxWidth;
public:
    RightCommand(controllers &c, CommandFactory &factory, int maxWidth);
    void execute()override;
    static std::unique_ptr<Command> construct(controllers &controller, CommandFactory &factory, int maxWidth);
};

#endif // RIGHTCOMMAND_H
