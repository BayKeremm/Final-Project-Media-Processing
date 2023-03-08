#include "command_factory.h"
#include "game.h"


#define DLOG(str)



CommandFactory::CommandFactory(controllers c, Game &game) : m_controllers{c}, m_game{game}{}


std::unique_ptr<Command> CommandFactory::createCommand(std::string command, std::vector<std::string> args){
    std::map<std::string,  std::unique_ptr<Command>(*)(controllers&, CommandFactory &factory)>::iterator it;
    std::unique_ptr<Command> newCommand = nullptr;

    DLOG(command)
    it = m_standardBuilders.find(command);
    if(it!=m_standardBuilders.end()){
        DLOG("Standard command !")
        newCommand = it->second(m_controllers, *this);
    }
    else{
        DLOG("Non standard command !")
        if(command == "down"){
            newCommand = DownCommand::construct(m_controllers, *this, m_game.getWorldHeight());
        }
        else if(command =="right"){
            newCommand = RightCommand::construct(m_controllers, *this, m_game.getWorldWidth());
        }
        else if(command == "goto"){
            if(args.size() >=2){
                try{
                    DLOG("First argument");
                    int x = std::stoi(args[0]);
                    DLOG("Second argument");
                    int y = std::stoi(args[1]);
                    newCommand = GotoCommand::construct(m_controllers, *this, m_game, x, y);
                }catch(std::invalid_argument e){
                    std::cout << "X and Y must be integer numbers" << std::endl;
                    PrintCommand::construct(m_controllers, *this, "X and Y must be integer numbers", m_game)->execute();
                    newCommand = Command::construct(m_controllers, *this);
                }catch(std::out_of_range e){
                    PrintCommand::construct(m_controllers, *this, "Please enter two coordinates", m_game)->execute();
                    newCommand = Command::construct(m_controllers, *this);
                }
            }
            else {
                PrintCommand::construct(m_controllers, *this, "Please enter two coordinates", m_game)->execute();
                newCommand = Command::construct(m_controllers, *this);
            }
        }
        else if(command == "moveTo"){
            try{
                newCommand = MovetoCommand::construct(m_controllers, *this, std::stoi(args[0]), std::stoi(args[1]), m_game);
            }catch(...){}
        }
        else if(command == "print"){
            QString arg;
            for(int i =0; i<args.size();i++){
                arg += QString::asprintf("%s ", args[i].c_str());
            }
            newCommand = PrintCommand::construct(m_controllers, *this, arg, m_game);
        }
    }

    return newCommand == nullptr ? std::move(HelpCommand::construct(m_controllers, *this)) : std::move(newCommand);
}


std::vector<std::string> CommandFactory::getCommands(){
    std::vector<std::string> commands = m_nonStandardBuilders;
    for(std::pair<std::string, std::unique_ptr<Command>(*)(controllers&, CommandFactory &factory)> pair : m_standardBuilders){
        commands.push_back(pair.first);
    }
    return commands;
}
