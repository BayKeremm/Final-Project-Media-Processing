#ifndef MOVETOCOMMAND_H
#define MOVETOCOMMAND_H

#include "command.h"

class Game;
class MovetoCommand : public Command
{

    int m_x, m_y;
    Game &m_game;
    float m_difficultyFactor;
public:
    MovetoCommand(controllers &c, CommandFactory &factory, int x, int y, Game &g);
    static std::unique_ptr<Command> construct(controllers &c, CommandFactory &factory, int x, int y, Game &g);
    void execute()override;
};

#endif // MOVETOCOMMAND_H
