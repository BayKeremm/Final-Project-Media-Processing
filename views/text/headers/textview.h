#ifndef TEXTVIEW_H
#define TEXTVIEW_H
#include <QTextDocument>
#include <QTextEdit>
#include "mainwindow.h"
#include <world.h>
#include <memory>

#include "controllers/enemy_controller.h"
#include "controllers/p_enemy_controller.h"
#include "controllers/healthpack_controller.h"
#include "controllers/protagonist_controller.h"

#define TILE_WIDTH 5
#define TEXT_WIDTH (TILE_WIDTH-1)

#define MAX_WIDTH 11
#define MAX_HEIGHT 9
#define BARS_LENGTH 25


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


struct controllers{
    std::vector<std::unique_ptr<EnemyController>> &enemies;
    //std::vector<std::unique_ptr<PEnemyController>> &pEnemies;
    std::vector<std::unique_ptr<HealthpackController>> &hPacks;
    std::unique_ptr<ProtagonistController> &protagonist;
};


class TextView
{
private:
    QString m_worldTemplate;

    //Those two are required, otherwise the text's spaces don't appear on windows, even when using &nbsp.
    const QString m_worldTemplatePre = "<pre>";
    const QString m_worldTemplatePost = "</pre>";


    controllers m_controllers;
    std::unique_ptr<QTextEdit> m_display;

    int m_worldHeight;
    int m_worldWidth;

    // Internal functions used to update the ASCII view.
    void loopFunction(QString &worldTemplate, int i, int j, worldGeneratorIterator data);
    void updateProtagonist(std::unique_ptr<ProtagonistController> & controller);
    void updateEnemies(std::vector<std::unique_ptr<EnemyController>> &enemies);
    void updateHPacks(std::vector<std::unique_ptr<HealthpackController>> &hPacks);    
    void cleanText();

public:
    TextView() = delete;

    TextView(MainWindow &parent,
             World& w, controllers controllers);


    /// @brief Updates the display of the text based view.
    void update();

    /// @brief hides the text based view
    void hide();

    /// @brief Shows the text based view
    void show();
};

#endif // TEXTVIEW_H
