#ifndef TEXTVIEW_H
#define TEXTVIEW_H
#include <QTextDocument>
#include <QTextEdit>
#include "mainwindow.h"
#include <world.h>
#include <memory>

#include "controllers/enemy_controller.h"
//#include "controllers/p_enemy_controller.h"
#include "controllers/healthpack_controller.h"
#include "controllers/protagonist_controller.h"
#include "controllers/controllers_struct.h"

#include "commands/command_factory.h"

#define TILE_WIDTH 5
#define TEXT_WIDTH (TILE_WIDTH-1)


#define MAX_WIDTH 11
#define MAX_HEIGHT 9
#define BARS_LENGTH 25


#define HORIZONTAL_OFFSET 20
#define VERTICAL_OFFSET 20

#if (TILE_WIDTH%2==0)
    #error Please select odd tile width
#endif

#if (MAX_HEIGHT%2==0)
    #error Please select odd MAX_HEIGHT
#endif

#if (MAX_WIDTH%2==0)
    #error Please select odd MAX_WIDTH
#endif


// Required for the ASCII generation.
struct worldGeneratorIterator{
    int minI;
    int minJ;
    int playerX;
    int playerY;
};



class TextView : public QObject
{
private:
    QString m_worldTemplate;

    //Those two are required, otherwise the text's spaces don't appear on windows, even when using &nbsp.
    QString m_worldTemplatePre = QString::asprintf("<pre style=\"overflow:hidden;font-size:12px;\">");
    const QString m_worldTemplatePost = "</pre>";


    QString m_barsPre = "<pre>";
    QString m_barsPost = "</pre>";
    QString m_worldData="";

    QString m_healthBar = "";
    QString m_energyBar = "";

    float m_scale= 12;

    controllers m_controllers;
    std::unique_ptr<QTextEdit> m_display;

    // used to generate the base grid indexes
    int m_worldHeight;
    int m_worldWidth;

    // Generator helpers
    bool m_didIndexShow = false;
    char m_prevIndexVal = 0;

    // Keeps a reference to the existing tiles
    std::vector<std::unique_ptr<Tile>> &m_tiles;

    // Internal functions used to update the ASCII view.
    void loopFunction(QString &worldTemplate, int i, int j, worldGeneratorIterator data);
    void updateProtagonist(std::unique_ptr<ProtagonistController> & controller);
    void updateEnemies(controllers c);
    void updateHPacks(std::vector<std::unique_ptr<HealthpackController>> &hPacks);
    void cleanText();

    // Input related fields and methods
    std::unique_ptr<QTextEdit> m_textInput;
    std::unique_ptr<QTextEdit> m_textFeedback;

    std::unique_ptr<CommandFactory> &m_cmdFactory;
    std::string autocompleteCommand(std::string);


public:
    TextView() = delete;

    TextView(MainWindow &parent,
             World& w, controllers controllers,
             std::vector<std::unique_ptr<Tile>> &tiles,
             std::unique_ptr<CommandFactory> &factory);

    void createWorldTemplate();


    /// @brief Updates the display of the text based view.
    void update();

    /// @brief hides the text based view
    void hide();

    /// @brief Shows the text based view
    void show();

    void setScale(float newScale);

    void commandResult(QString text);

// This is used to be notified by the textInput that the content has changed
public slots:
    void textInputTextChanged();
    void playerEnergyChanged(int e);
    void playerHealthChanged(int h);
};

#endif // TEXTVIEW_H
