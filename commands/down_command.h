#ifndef DOWNCOMMAND_H
#define DOWNCOMMAND_H
#include "commands/command.h"

class DownCommand : public Command
{
private:
    int m_maxHeight;
public:
    DownCommand(controllers &c, CommandFactory &factory, int maxHeight);
    void execute() override;
    static std::unique_ptr<Command> construct(controllers &c, CommandFactory &factory, int maxHeight);
};

#endif // DOWNCOMMAND_H
