#include "print_command.h"
#include "game.h"

PrintCommand::PrintCommand(controllers &controller, CommandFactory &factory, QString toPrint, Game &game) : Command(controller, factory), m_toPrint{toPrint}, m_game{game}
{

}

void PrintCommand::execute(){
    m_game.textCommandFeedback(m_toPrint);
}


std::unique_ptr<Command> PrintCommand::construct(controllers &controller, CommandFactory &factory, QString toPrint, Game &game){
    return std::make_unique<PrintCommand>(controller, factory, toPrint, game);
}
