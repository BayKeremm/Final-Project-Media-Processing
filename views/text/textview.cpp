#include "textview.h"
#include <iostream>
#include <QRegularExpression>

#include <cmath>


bool isTilePoisonned(int index, controllers &c);



#define DLOG(str)

TextView::TextView(MainWindow &parent, World &w, controllers controllers, std::vector<std::unique_ptr<Tile>> &tiles, std::unique_ptr<CommandFactory> &factory) :
    m_controllers{controllers},
    m_tiles {tiles},
    m_cmdFactory{factory}
{
    m_worldHeight = w.getRows();
    m_worldWidth = w.getCols();
    m_display = std::make_unique<QTextEdit>(&parent);
    m_display -> setReadOnly(true);
    m_display -> setAcceptRichText(true);
    m_display->resize(631, 627);
    m_display->move(HORIZONTAL_OFFSET, VERTICAL_OFFSET);
    m_display->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    m_display->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    m_display->hide();

    m_textInput = std::make_unique<QTextEdit>(&parent);
    m_textInput->setAcceptRichText(false);
    m_textInput->resize(631, 30);
    m_textInput->setPlaceholderText("Command");

    m_textInput->move(HORIZONTAL_OFFSET, 630 + VERTICAL_OFFSET);

    m_textFeedback = std::make_unique<QTextEdit>(&parent);
    m_textFeedback->resize(631, 60);
    m_textFeedback->move(HORIZONTAL_OFFSET, 630 + VERTICAL_OFFSET);
    m_textFeedback->setReadOnly(true);
    m_textFeedback->setPlaceholderText("Commands results");
    m_textInput->move(HORIZONTAL_OFFSET, 689 + VERTICAL_OFFSET);

    m_worldTemplate = "";

    m_healthBar ="<div style=\"font-size:18px\">Health: [";
    for(int i=0; i<BARS_LENGTH;i++){
        m_healthBar+="#";
    }
    m_healthBar +="]<br/>";
    m_energyBar = "Energy: [";
    for(int i=0; i<BARS_LENGTH;i++){
        m_energyBar+="#";
    }
    m_energyBar +="]</div>\n";


    QObject::connect(m_textInput.get(), &QTextEdit::textChanged, this, &TextView::textInputTextChanged);


    parent.setFixedSize(m_display->width() + 200 + HORIZONTAL_OFFSET,
                        m_display->height() + m_textInput->height() + 20 + m_textFeedback->height() + VERTICAL_OFFSET);
}



/// @brief Generates the ASCII world character by character, places the player in the world and creates unique box identifiers.
/// @param world A reference to the QText that holds the text and that needs to be updated.
/// @param i The current row counter
/// @param j The current column counter
/// @param data The minimum value for the row and column counters as well as the character's position.
void TextView::loopFunction(QString &world, int i, int j, worldGeneratorIterator data){

    /**Logic of the comparison:
     * 
     * NOTE: since this generation method is used for both j and i, and the same conditions apply to each of them,
     * as we go further, they will be referenced to as "counter".
     * 
     * A box has the following layout:
     * 
     *       Length of TILE_WIDTH characters (in practice 2TILE_WIDTH-2 to have equal height and distance)
     *      +------+
     *      |      |
     *      |   µ{row number}µ{column number}   |  Height of TILE_WIDTH charaters
     *      |      |
     *      +------+
     * 
     * The generator has 3 identical states for columns and rows:
     *      -At the first row/column of the string
     *      -In an intermediary row or column of the box
     *      -At the last row/column of the box.
     * 
     * Any combination of 2 in the 3 states is possible.
     * 
     * The logic is the following:
     *  - If we are at the end of a box, we want to display an edge. Thus each box is actually generated like this:
     * 
     *                         New box:
     *                                  
     *             |                  |
     *             |     <---         |
     *             |                  |
     *       ------+            ------+
     * 
     * We thus need to know when we are at the last column or row of a box. This is the condition:
     *                              
     *                          counter%TEXT_WIDTH == TEXT_WIDTH -1
     *
     *      --Note that in the actual code, the condition is reversed. There is no particular reason for this.--
     * 
     * We then need to be able to add white spaces in the box. This is the case when the above condition is not fulfilled.
     * However, one can quickly notice that just implementing the two possibilities would result in a grid looking like this:
     * 
     * 
     *             |        |
     *             |        |
     *             |        |
     *             |        |
     *     --------+--------+
     * 
     * We thus add an additional condition to fit the first row and column borders:
     * 
     *                              counter==0
     * 
     * With this, two problems can be noted. 
     *  1. Our counters are not always initialized to 0
     *  2. The first box of each row will be less wide and the first box of each column will be less tall.
     * 
     * To solve these problems, we refined two conditions. The first one becomes:
     * 
     *                  (counter-1)%TEXT_WIDTH == TEXT_WIDTH -1
     * 
     * to compensate for the change in width and height and the second condition becomes
     * 
     *                          counter == minCounter
     * 
     * with minCounter, the minimum value of the counter in the current run.
     * (if you don't know why countre is not always 0, cfr documentation of updateProtagonist.)
     *
     *
     *
     * Aditional note:
     *  Conditions with the counters being smaller than their registered minimum were added to have indices
     *  showing up on the grid. Those check if there is one line space between the index and the start of the grid
     *  (checking if the index is == to the minimum -2) and if that is the case, if the index is centered with its box.
    */

    // To show the column number

    int relativeJ = data.minJ + (int) floor((j-data.minJ)/TEXT_WIDTH);
    int relativeI = data.minI + (int) floor((i-data.minI)/TEXT_WIDTH);

    if(i == data.minI-2){
        if((j-data.minJ)%TEXT_WIDTH == TEXT_WIDTH/2 && j> data.minJ){
            world += QString::asprintf("%d", relativeJ);
            m_didIndexShow = true;
        }
        else{
            if(m_didIndexShow){
                if(relativeJ < 10){
                    world+= "  ";
                }
                else if(relativeJ < 100){
                    world+= " ";
                    m_prevIndexVal=0;
                }
                m_didIndexShow = false;
            }
            else{
                if(m_prevIndexVal>=1){
                    world += " ";
                    m_prevIndexVal --;
                }
                else{
                    world +="  ";
                }
            }
        }
    }
    else if(i==data.minI){
        if(j<data.minJ){
            world += "  ";
        }
        else if(j==data.minJ){
            world += "+";
        }
        else if((j-1-data.minJ)%TEXT_WIDTH!= TEXT_WIDTH-1 ){
            world += "——";
        }
        else{
            world += "+";
        }
    }
    else if( i> data.minI && (i-1-data.minI)%TEXT_WIDTH != TEXT_WIDTH-1 ){

        // To show the row index
        if(j==data.minJ-2){
            if((i-data.minI)%TEXT_WIDTH == TEXT_WIDTH/2)
                if (relativeI <10)
                    world += " " +QString::asprintf("%d", relativeI);
                else
                    world += QString::asprintf("%d", relativeI);
            else
                world += "  ";
        }

        else if(j==data.minJ){
            world+= "|";
        }

        else if((j-1-data.minJ)%TEXT_WIDTH != TEXT_WIDTH-1 ){

            if((i-data.minI)%TEXT_WIDTH == TEXT_WIDTH/2 && (j-data.minJ)%TEXT_WIDTH == TEXT_WIDTH/2){

                if(relativeI == data.playerY && relativeJ == data.playerX){
                    if(isTilePoisonned(relativeJ + m_worldWidth*relativeI, m_controllers)){
                        world +="<span style=\"background-color: rgba(121, 0, 121,";
                    }
                    else{
                        world +="<span style=\"background-color: rgba(0, 0, 0,";
                    }
                    world += QString::asprintf("%f", 1-m_tiles[relativeJ + m_worldWidth*relativeI]->getValue());
                    world += ");\">";
                    world += m_controllers.protagonist->getTextView()->print();
                    world += "</span>";
                }
                else{
                    if(isTilePoisonned(relativeJ + m_worldWidth*relativeI, m_controllers)){
                        world +="<span style=\"background-color: rgba(121, 0, 121,";
                    }
                    else{
                        world +="<span style=\"background-color: rgba(0, 0, 0,";
                    }
                    world += QString::asprintf("%f", 1-m_tiles[relativeJ + m_worldWidth*relativeI]->getValue());
                    world += ");\">";
                    world += "a" + QString::asprintf("%d", relativeJ  );
                    world += "a" + QString::asprintf("%d", relativeI );
                    world += "</span>";
                }
            }
            else if(j>data.minJ){
                if(isTilePoisonned(relativeJ + m_worldWidth*relativeI, m_controllers)){
                    world +="<span style=\"background-color: rgba(121, 0, 121,";
                }
                else{
                    world +="<span style=\"background-color: rgba(0, 0, 0,";
                }
                world += QString::asprintf("%f", 1-m_tiles[relativeJ + m_worldWidth*relativeI]->getValue());
                world += ");\">  </span>";
            }
            else world += "  ";
        }
        else if (j>data.minJ){
            world += "|";
        }
    }
    else if (i> data.minI){
        if(j<data.minJ){
            world += "  ";
        }
        else if(j==data.minJ){
            world +="+";
        }
        else if((j-1-data.minJ)%TEXT_WIDTH != TEXT_WIDTH-1){
            world +="——";
        }
        else{
            world +="+";
        }
    }
}



/// @brief Creates the base of the visible ASCII world and adds the player in it. 
/// @param controller A reference to a unique pointer of the protagonist's controller used to get the health, energy and position.
void TextView::updateProtagonist(std::unique_ptr<ProtagonistController> &controller){
    std::unique_ptr<Protagonist> &model = controller->getModel();

    //gets the character's position and Energy/health
    int xPos = model->getXPos();
    int yPos = model->getYPos();

    /**Sets the initial indexes for the Grid generation.
     * Logic: 
     *      -j is the column counter for the ASCII text generator
     *      -i is the row column counter for the ASCII text generator
     *      -MAX_HEIGHT and MAX_WIDTH are the maximum height and width of the grid, counted in boxs (thus independent of the box size).
     *      -We don't want the grid to overflow the QTextEdit
     * 
     * We thus calculate an initial i and j for the loop that will generate the grid around the player position. We try to keep the player's position
     * always centered on the screen for ease of readability. However, that is not possible if the player is too close to any border of the world.
     * 
     * Solution:
     *  If the player is too close to an edge to be displayed at the center of the grid, we simply set the i and j to be either 0 or 
     * the maximum size of the world minus the height and/or width of the display window.
     * 
     * Example: 
     *  The player is in x=2, y=2 and MAX_WIDTH=9, MAX_HEIGHT=5. The player will appear in x=2 and y=2 on the grid as it is too close to the top-left corner
     * of the world. A second example is the same MAX_WIDTH and MAX_HEIGHT, but the player positionned at x=world_width-2 and y=world_height-10.
     * The player will thus appear in the box located at x=7 and y=3 on the display grid, as it is too close to the right border to be properly displayed, centered
     * in the width, but it will appear in y=3, as it ishigh enough to be displayed there.
    */
    int j = xPos-MAX_WIDTH/2 < 0 ? 0 : xPos + MAX_WIDTH/2 > m_worldWidth -1 ? m_worldWidth - MAX_WIDTH : xPos - MAX_WIDTH/2 ;
    int i = yPos-MAX_HEIGHT/2 < 0 ? 0 : yPos + MAX_HEIGHT/2 > m_worldHeight-1 ? m_worldHeight - MAX_HEIGHT : yPos - MAX_HEIGHT/2 ;

    //Sets additional data the text generator will need to display a nice grid.
    worldGeneratorIterator data;
    data.minI = i;
    data.minJ = j;
    data.playerX = xPos;
    data.playerY = yPos;

    // This is done to indicate the column an row number
#ifdef SHOW_INDEX
    i -=2;
    j-=2;
#endif //SHOW_INDEX
    // Loops in the visible surroundings of the protagonist
    while(i<=data.minI+(MAX_HEIGHT*TEXT_WIDTH) ){
        while(j<=data.minJ+(MAX_WIDTH*TEXT_WIDTH) ){
            //Adds the text to the world template
            loopFunction(m_worldTemplate, i, j, data);
            j++;
        }
        i++;
        // -2 is to print the row numbers
        #ifdef SHOW_INDEX
        j=data.minJ -2;
        #else
        j = data.minJ;
        #endif //SHOW_INDEX
        m_worldTemplate += "<br/>";
    }
}



/// @brief Places the enemies on the ASCII world.²
/// @param enemies A reference to a vector of enemy controller used to get the positions.
void TextView::updateEnemies(controllers c){
    for(std::unique_ptr<EnemyController> & enemy : c.enemies){
        std::unique_ptr<Enemy> &model = enemy->getModel();
        QRegularExpression regex(QString::asprintf("\\ba%da%d\\b", model->getXPos(), model->getYPos()));

        m_worldTemplate.replace(regex, enemy->getTextView()->print());
    }
    for(std::unique_ptr<XEnemyController> & enemy : c.xEnemies){

        std::unique_ptr<Enemy> &model = enemy->getModel();

        QRegularExpression regex(QString::asprintf("\\ba%da%d\\b", model->getXPos(), model->getYPos()));

        m_worldTemplate.replace(regex, enemy->getTextView()->print());
    }
    for(std::unique_ptr<PEnemyController> & enemy : c.pEnemies){
        std::unique_ptr<Enemy> &model = enemy->getModel();
        QRegularExpression regex(QString::asprintf("\\ba%da%d\\b", model->getXPos(), model->getYPos()));

        m_worldTemplate.replace(regex, enemy->getTextView()->print());
    }

}




/// @brief Places the health packs on the ASCII world.
/// @param enemies A reference to a vector of health packs controller used to get the positions.
void TextView::updateHPacks(std::vector<std::unique_ptr<HealthpackController>> &hPacks){
    for(std::unique_ptr<HealthpackController> & hPack : hPacks){
        std::unique_ptr<Tile> &model = hPack->getModel();
        QRegularExpression regex(QString::asprintf("\\ba%da%d\\b", model->getXPos(), model->getYPos()));
        m_worldTemplate.replace(regex, hPack->getTextView()->print());
    }
}




/// @brief Cleans the remaining unique identifiers to get a clean grid.
void TextView::cleanText(){
    QRegularExpression regex("a[0-9]+a[0-9]+");
    m_worldTemplate.replace(regex, "  ");
}





void TextView::hide(){
    m_display->hide();
    m_textInput->hide();
    m_textFeedback->hide();
}

void TextView::show(){
    m_display->show();
    m_textInput->show();
    m_textFeedback->show();
}



void TextView::textInputTextChanged(){
    // Checks if the user has confirmed their choice
    if(m_textInput->toPlainText().contains("\n")){
        // retrieves the text and strips the new line from it
        QString input = m_textInput->toPlainText().remove("\n");
        // Splits the text arguments and autocompletes the command
        QStringList inputs = input.split(" ");
        std::string command = autocompleteCommand(inputs[0].toStdString());
        std::vector<std::string> args;

        // If the command was not found, leaves the text inside the text editor.
        // We set the text in the holder so the new line diappear
        if(command == ""){
            m_textInput->setPlainText(input);

            //moves the cursor to the end of the input
            QTextCursor cursor = QTextCursor(m_textInput->document());
            cursor.movePosition(QTextCursor::End);
            m_textInput->setTextCursor(cursor);

            return;
        }


        if(command=="down"){
            args.push_back( std::to_string(m_worldHeight-1) );
        }
        else if(command=="right"){
            args.push_back( std::to_string(m_worldWidth-1) );
        }


        for(int i=1; i<inputs.length(); i++){
            args.push_back(inputs[i].toStdString());
        }

        std::unique_ptr<Command> cmd = m_cmdFactory->createCommand(command, args);
        DLOG("Executing command");

        cmd->execute();
        DLOG("Command executed");
        m_textInput->clear();
    }
    else if(m_textInput->toPlainText().contains("\t")){
        QString input = m_textInput->toPlainText().remove("\t");
        // Splits the text arguments and autocompletes the command
        QStringList inputs = input.split(" ");
        std::string command = autocompleteCommand(inputs[0].toStdString());
        if(command == ""){
            m_textInput->setPlainText(input);
        } else{
            QString txt = QString::asprintf("%s", command.c_str());
            for(int i=1; i<inputs.length(); i++){
                txt += " "+inputs[i];
            }
            m_textInput->setPlainText(txt);
        }
        //moves the cursor to the end of the input
        QTextCursor cursor = QTextCursor(m_textInput->document());
        cursor.movePosition(QTextCursor::End);
        m_textInput->setTextCursor(cursor);
    }
}

std::string TextView::autocompleteCommand(std::string input){
    std::string completedCommand = "";
    bool wasFound=false;

    for(std::string availableCommand : m_cmdFactory->getCommands()){
        size_t position = availableCommand.find(input, 0);
        if(position == 0){
            DLOG("Command found: " << availableCommand << " at position: " << position);
            if (wasFound) return "";
            completedCommand = availableCommand;
            wasFound = true;
        }
    }

    return completedCommand;
}


void TextView::update(){
    m_worldTemplate.clear();

    updateProtagonist(m_controllers.protagonist);
    updateEnemies(m_controllers);
    updateHPacks(m_controllers.hPacks);
    cleanText();

    m_display->setHtml(m_barsPre + m_healthBar + m_energyBar + m_barsPost + m_worldTemplatePre + m_worldTemplate + m_worldTemplatePost);
}




void TextView::playerEnergyChanged(int e){

    e = e*BARS_LENGTH/100;

    m_energyBar ="Energy: [";
    for(int i=0; i<BARS_LENGTH;i++){
        if(i<e)m_energyBar+="#";
        else m_energyBar+=" ";
    }
    m_energyBar +="]</div>\n";
}

void TextView::playerHealthChanged(int h){

    DLOG("Health changed: " << h);

    h = h*BARS_LENGTH/100;

    // Creates the indicators for the health and energy
    m_healthBar ="<div style=\"font-size:18px\">Health: [";
    for(int i=0; i<BARS_LENGTH;i++){
        if(i<h)m_healthBar+="#";
        else m_healthBar+=" ";
    }
    m_healthBar +="]<br/>";
}



bool isTilePoisonned(int index, controllers &c){
    for(poisened_tile_t t : c.poisonedTiles){
        if(t.index_t == index && t.active_t) return true;
    }
    return false;
}

void TextView::commandResult(QString text){
    QString history = m_textFeedback->toPlainText();
    if (history == "") m_textFeedback->setPlainText(text);
    else m_textFeedback->setPlainText(history+"\n"+text);

    // Scroll to the end of the document
    QTextCursor cursor = QTextCursor(m_textFeedback->document());
    cursor.movePosition(QTextCursor::End);
    m_textFeedback->setTextCursor(cursor);
}

void TextView::setScale(float newScale){
    m_scale = m_scale*newScale;

    m_scale = m_scale<1 ? 1 : m_scale> 384 ? 384 : m_scale;

    m_worldTemplatePre = QString::asprintf("<pre style=\"overflow:hidden;font-size:%dpx;\">", (int)m_scale );
}
