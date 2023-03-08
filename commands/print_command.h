#ifndef PRINTCOMMAND_H
#define PRINTCOMMAND_H

#include "command.h"

class Game;
class PrintCommand : public Command
{
private:
    QString m_toPrint;
    Game &m_game;
public:
    PrintCommand(controllers &controller, CommandFactory &factory, QString toPrint, Game &game);
    void execute()override;
    static std::unique_ptr<Command> construct(controllers &controller, CommandFactory &factory, QString toPrint, Game &game);
};

#endif // PRINTCOMMAND_H
