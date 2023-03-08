#include "goto_command.h"

#include "pathfinder/astar.h"

#include <iostream>
#include "game.h"

#define DLOG(str) std::cout << "[Goto] " << str << std::endl;

GotoCommand::GotoCommand(controllers &c, CommandFactory &factory, Game &game, int x, int y) : Command(c, factory), m_x{x}, m_y{y}, m_game{game}
{
}

void GotoCommand::execute(){
    if(m_game.moving()) return;
    m_game.stopUpdateTimer();
    std::clock_t c_start = std::clock();
    std::vector<Node*> path =  m_controllers.astar->findPath(m_player->getXPos(), m_player->getYPos(), m_x, m_y);
    std::clock_t c_end = std::clock();
    long time_elapsed_ms = 1000.0 * (c_end-c_start) / CLOCKS_PER_SEC;
    std::cout << "CPU time used: " << time_elapsed_ms << " ms\n";

    std::reverse(path.begin(), path.end());
    m_game.addPathToQueue(path);
    
    m_game.startUpdateTimer();
}

std::unique_ptr<Command> GotoCommand::construct(controllers &controller, CommandFactory &factory, Game & game, int x, int y){
    return std::make_unique<GotoCommand>(controller, factory, game, x, y);
}
