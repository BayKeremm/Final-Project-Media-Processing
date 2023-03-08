#ifndef GOTOCOMMAND_H
#define GOTOCOMMAND_H

#include "command.h"

class Game;
class GotoCommand : public Command
{
private:
    int m_x, m_y;
    Game &m_game;
public:
    GotoCommand(controllers &c, CommandFactory &factory, Game &game, int x, int y);
    static std::unique_ptr<Command> construct(controllers &controller, CommandFactory &factory, Game &game, int x, int y);
    void execute()override;
};

#endif // GOTOCOMMAND_H
