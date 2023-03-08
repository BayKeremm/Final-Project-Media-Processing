#ifndef GAME_H
#define GAME_H

#include "controllers/enemy_controller.h"
#include "controllers/healthpack_controller.h"
#include "controllers/p_enemy_controller.h"
#include "controllers/poisened_tile_struct.h"
#include "controllers/protagonist_controller.h"
#include "controllers/x_enemy_controller.h"
#include "pathfinder/astar.h"
#include "qradiobutton.h"
#include "world.h"
#include <QFileDialog>
#include <QGraphicsScene>
#include <QGraphicsView>
#include <QInputDialog>
#include <QLabel>
#include <QMessageBox>
#include <QObject>
#include <QPushButton>
#include <QSlider>
#include <QWidget>
#include <cmath>
#include <iostream>
#include <memory.h>
#include <vector>

#include "views/graphics/graphics_view.h"
#include "views/text/textview.h"

using std::vector, std::unique_ptr;

class Game : public QObject {
  Q_OBJECT
public:
  Game(MainWindow *parent);

  // VIEW
  void showView();
  void showGraphics();
  void showText();


  // MOVEMENT
  void moveProtagonist();
  void keyMove(int m);
  void moveTo(int x, int y);
  bool moving() { return m_solIndex < (int)m_sol.size(); };
  void moveXEnemies();

  // TIMER
  // checks if tile of protagonist is poisoned every 1 second
  // poisons protagonist is true every second hes on it
  void checkIfPoisened();

  // GAME
  void gameInit();
  void autoMove();
  void win();
  void lose();
  void endGame();
  void resetData();

  float getDifficultyfactor() const { return m_difficultyFactor; };
  float getPathWeight() { return pathW; };
  float getHeuristicWeight() { return heuristicW; };
  QString getFileName() { return filename; };

  int getWorldWidth() { return m_world.getCols(); }
  int getWorldHeight() { return m_world.getRows(); }
  std::vector<std::unique_ptr<Tile>> &getTiles() { return m_tiles; }

  void drawPastTile(int x, int y);
  void drawPoisonnedTile(int px, int py, PEnemy &pEnemy);

  void stopUpdateTimer();
  void startUpdateTimer();

  void addPathToQueue(vector<Node *> newPath);

    void textCommandFeedback(QString val);

public slots:
  // TIMER
  void updateGame();

  // UI
  void showUI();
  void hideUI();
  // setters for keyboard and mouse input
  void setKey(int key) { m_key = key; };
  void pathToPoint(QPoint position);
  void switchView();

  // void playerPositionChanged(int x, int y);
  void selectFile();
  void heuristicChanged(float newHeuristic);
  void pathWeightChanged(float newPathWeight);
  void scaleChanged(float newScale);
  void changeGameMode() { m_autoplay = !m_autoplay; };
  void difficultyChanged();
  void refreshRateChanged(int new_refresh) { m_refreshTime = new_refresh; };

  void playerEnergyChanged(int e);
  void playerHealthChanged(int h);

private:


  // two main views
  unique_ptr<GraphicsView> m_gView;
  unique_ptr<TextView> m_tView;

  World m_world;
  QString filename = "";
  int m_enemyNumber = 0;
  int m_hpNumber = 0;
  float m_pEnemyRatio = 0.f;
  MainWindow *m_parent;

  int prev_slider_value = 50;
  float m_scaleValue = 1.0;

  // UI
  QPushButton *m_file_button;

  QLabel *m_welcomeLabel;

  QPushButton *m_view_button;
  bool m_defaultView = true; // default view is graphics
  QPushButton *m_autoplay_button;

  unique_ptr<QLabel> m_heuristic_text;
  QSlider *m_heuristicSlider;
  float heuristicW = 0;
  unique_ptr<QLabel> m_path_text;
  QSlider *m_pathSlider;
  float pathW = 0;
  unique_ptr<QLabel> m_difficulty_text;
  QRadioButton *m_easyBtn;
  QRadioButton *m_mediumBtn;
  QRadioButton *m_hardBtn;
  unique_ptr<QLabel> m_refresh_text;
  QSlider *m_refreshSlider;
  unique_ptr<QLabel> m_zoom_text;
  QSlider *m_zoomSlider;


  // TIMER
  unique_ptr<QTimer> m_refreshTimer = nullptr;
  int m_iter = 0;

  // MOVEMENT
  int m_key = -1;
  unique_ptr<Astar> m_astar = nullptr;
  vector<Node *> m_sol = {};
  int x = 0;
  int y = 0;
  int m_solIndex = 0;

  // GAME SETTINGS
  bool view = false;
  int m_refreshTime = 50;
  float m_difficultyFactor = 2; // realistic between 1 (hard) and 3 (easy)
  bool m_autoplay = false;
  const float m_maxEnergy = 100.0f;
  const float m_maxHealth = 100.0f;

  // VECTORS OF TILES
  vector<unique_ptr<Tile>> m_tiles;
  vector<unique_ptr<Enemy>> m_enemies;
  vector<unique_ptr<Tile>> m_hPacks;
  int m_countLiveEnemies;

  // poisened tiles struct vector
  vector<poisened_tile_t> poisonedTiles;

  // CONTROLLERS
  vector<unique_ptr<EnemyController>> m_enemyControllers;
  vector<unique_ptr<PEnemyController>> m_pEnemyControllers;
  vector<unique_ptr<XEnemyController>> m_xEnemyControllers;
  vector<unique_ptr<HealthpackController>> m_healthPackControllers;
  unique_ptr<ProtagonistController> m_protagonistController;

  std::unique_ptr<CommandFactory> m_cmdFactory;

  int countAliveEnemies();

};

#endif // GAME_H
