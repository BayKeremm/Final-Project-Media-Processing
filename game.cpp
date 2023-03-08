#include "game.h"
#include "QtWidgets/qgridlayout.h"
#include "controllers/controllers_struct.h"

#include <iostream>
#define DLOG(str)

Game::Game(MainWindow *parent) {
  // keep the parent pointer in the class to use it in the initGame
  m_parent = parent;

  // UI
  // select file button
  m_file_button = new QPushButton("SELECT FILE", parent);
  m_file_button->setGeometry(660, 20, 100, 40);
  m_file_button->show();
  connect(m_file_button, SIGNAL(clicked()), this, SLOT(selectFile()));

  // heuristic weight text
  m_heuristic_text = std::make_unique<QLabel>(parent);
  m_heuristic_text->setText("HEURISTIC:"); // define energy text
  m_heuristic_text->setFont(QFont("roboto", 10));
  m_heuristic_text->move(660, 70);
  m_heuristic_text->hide();
  // heuristic weight slider
  m_heuristicSlider = new QSlider(Qt::Horizontal, parent);
  m_heuristicSlider->move(660, 100);
  m_heuristicSlider->setMinimum(0);
  m_heuristicSlider->setMaximum(10);
  m_heuristicSlider->setTickInterval(2);
  m_heuristicSlider->setSingleStep(2);
  m_heuristicSlider->setTickPosition(QSlider::TicksAbove);
  m_heuristicSlider->hide();
  QObject::connect(m_heuristicSlider, &QSlider::valueChanged, this,
                   &Game::heuristicChanged);

  // path weight text
  m_path_text = std::make_unique<QLabel>(parent);
  m_path_text->setText("PATH WEIGHT:"); // define energy text
  m_path_text->setFont(QFont("roboto", 10));
  m_path_text->move(660, 130);
  m_path_text->hide();
  // path weight slider
  m_pathSlider = new QSlider(Qt::Horizontal, parent);
  m_pathSlider->move(660, 160);
  m_pathSlider->setMinimum(0);
  m_pathSlider->setMaximum(10);
  m_pathSlider->setTickInterval(2);
  m_pathSlider->setSingleStep(2);
  m_pathSlider->setTickPosition(QSlider::TicksAbove);
  m_pathSlider->hide();
  QObject::connect(m_pathSlider, &QSlider::valueChanged, this,
                   &Game::pathWeightChanged);

  // difficulty text
  m_difficulty_text = std::make_unique<QLabel>(parent);
  m_difficulty_text->setText("DIFFICULTY");
  m_difficulty_text->setFont(QFont("roboto", 10));
  m_difficulty_text->move(660, 190);
  m_difficulty_text->hide();
  // difficulty slider TODO should be a slider IMO
  m_easyBtn = new QRadioButton("EASY", m_parent);
  m_easyBtn->move(660, 210);
  m_easyBtn->hide();
  QObject::connect(m_easyBtn, SIGNAL(clicked()), this,
                   SLOT(difficultyChanged()));
  m_mediumBtn = new QRadioButton("MEDIUM", m_parent);
  m_mediumBtn->move(660, 230);
  m_mediumBtn->click(); // MEDIUM DEFAULT
  m_mediumBtn->hide();
  QObject::connect(m_mediumBtn, SIGNAL(clicked()), this,
                   SLOT(difficultyChanged()));
  m_hardBtn = new QRadioButton("HARD", m_parent);
  m_hardBtn->move(660, 250);
  m_hardBtn->hide();
  QObject::connect(m_hardBtn, SIGNAL(clicked()), this,
                   SLOT(difficultyChanged()));

  // refresh text
  m_refresh_text = std::make_unique<QLabel>(parent);
  m_refresh_text->setText("REFRESH TIME:"); // define energy text
  m_refresh_text->setFont(QFont("roboto", 10));
  m_refresh_text->move(660, 280);
  m_refresh_text->hide();
  // refresh slider
  m_refreshSlider = new QSlider(Qt::Horizontal, parent);
  m_refreshSlider->move(660, 310);
  m_refreshSlider->setMinimum(20);
  m_refreshSlider->setValue(m_refreshTime);
  m_refreshSlider->setMaximum(80);
  m_refreshSlider->setTickInterval(10);
  m_refreshSlider->setSingleStep(10);
  m_refreshSlider->setTickPosition(QSlider::TicksAbove);
  m_refreshSlider->hide();
  QObject::connect(m_refreshSlider, &QSlider::valueChanged, this,
                   &Game::refreshRateChanged);

  // zoom dial text
  m_zoom_text = std::make_unique<QLabel>(parent);
  m_zoom_text->setText("ZOOM:");
  m_zoom_text->setFont(QFont("roboto", 10));
  m_zoom_text->move(660, 340);
  m_zoom_text->hide();
  // zoom slider
  m_zoomSlider = new QSlider(Qt::Horizontal, parent);
  m_zoomSlider->move(660, 370);
  m_zoomSlider->setMinimum(0);
  m_zoomSlider->setMaximum(50);
  m_zoomSlider->setValue(25);
  m_zoomSlider->setTickInterval(5);
  m_zoomSlider->setSingleStep(5);
  m_zoomSlider->setTickPosition(QSlider::TicksAbove);
  m_zoomSlider->hide();
  QObject::connect(m_zoomSlider, &QSlider::valueChanged, this,
                   &Game::scaleChanged);

  // autoplay button
  m_autoplay_button = new QPushButton("AUTOPLAY", parent);
  m_autoplay_button->setGeometry(660, 420, 100, 40);
  m_autoplay_button->hide();
  connect(m_autoplay_button, SIGNAL(clicked()), this, SLOT(changeGameMode()));

  // switch view button
  m_view_button = new QPushButton("SWITCH VIEW", parent);
  m_view_button->setGeometry(660, 480, 100, 40);
  m_view_button->hide();
  connect(m_view_button, SIGNAL(clicked()), this, SLOT(switchView()));

  // initialize m_refreshTimer
  m_refreshTimer = std::make_unique<QTimer>(this);
  connect(m_refreshTimer.get(), SIGNAL(timeout()), this, SLOT(updateGame()));

  // show amazing art of Kerem
  m_welcomeLabel = new QLabel(m_parent);
  QPixmap pixmap(":/images/welcome.png");
  m_welcomeLabel->setGeometry(0, 0, 700, 700);
  m_welcomeLabel->setPixmap(pixmap.scaled(700, 700, Qt::KeepAspectRatio));
  m_welcomeLabel->show();
}

void Game::selectFile() {
  filename = QFileDialog::getOpenFileName(m_parent, tr("Select file"), "",
                                          "Png File (*.png)");
  // check if file is selected
  if (filename != "") {
    // get number of enemies
    m_enemyNumber = QInputDialog::getInt(m_parent, "Open map",
                                         "Number of enemies:", 10, 0, 255, 1);
    // get number of healthpacks
    m_hpNumber = QInputDialog::getInt(m_parent, "Open map",
                                      "Number of health packs:", 10, 0, 255, 1);
    // get ratio of poisoned enemies
    m_pEnemyRatio = QInputDialog::getInt(m_parent, "Open map",
                                         "Poisoned enemy %:", 50, 0, 100, 5) /
                    100;

    // start game
    gameInit();
  }
}

// INIT GAME
void Game::gameInit() {

  // show UI
  showUI();

  // initialize world
  m_world = World();
  m_world.createWorld(filename, m_enemyNumber, m_hpNumber, m_pEnemyRatio);

  m_tiles = m_world.getTiles();
  m_enemies = m_world.getEnemies();
  m_hPacks = m_world.getHealthPacks();

  // initialize Astar variables
  vector<Node> nodes;
  nodes.reserve(m_world.getRows() * m_world.getCols());
  for (auto &t : m_tiles) {
    // std::cout << t->getXPos() << ", " << t->getYPos() << ", " <<
    // t->getValue()<< std::endl;
    if (t->getValue() == std::numeric_limits<float>::infinity()) {
      nodes.emplace_back(t->getXPos(), t->getYPos(), 2, 0, 0, nullptr);
    } else {
      nodes.emplace_back(t->getXPos(), t->getYPos(), t->getValue(), 0, 0,
                         nullptr);
    }
  }
  m_astar =
      std::make_unique<Astar>(nodes, m_world.getRows(), m_world.getCols());

  // keep count of how many enemies are in the game
  m_countLiveEnemies = m_enemies.size();

  std::cout << "print special tiles as x,y,value,defeated,poison" << std::endl;

  auto dummy_penemy = std::make_unique<PEnemy>(1, 1, 1);
  int xEnemyCount = 0;
  // initialize enemy controllers
  for (auto &enemy : m_enemies) {
    if (typeid(*dummy_penemy) == typeid(*enemy)) {
      DLOG("penemy: " << enemy->serialize());

      auto ex = enemy->getXPos();
      auto ey = enemy->getYPos();

      nodes[ey * m_world.getCols() + ex].setFlag(3);

      unique_ptr<PEnemyController> controller =
          std::make_unique<PEnemyController>(std::move(enemy));
      m_pEnemyControllers.push_back(std::move(controller));
    } else {
      auto ex = enemy->getXPos();
      auto ey = enemy->getYPos();
      nodes[ey * m_world.getCols() + ex].setFlag(3);

      // if xEnemyCount < enemyCount * %pEnemy * %xEnemy
      if (xEnemyCount < (m_countLiveEnemies * 0.3 * 0.3)) {
        DLOG("xenemy: " << enemy->serialize());
        unique_ptr<XEnemyController> controller =
            std::make_unique<XEnemyController>(std::move(enemy));
        m_xEnemyControllers.push_back(std::move(controller));
        xEnemyCount++;
      } else {
        DLOG("enemy: " << enemy->serialize());
        unique_ptr<EnemyController> controller =
            std::make_unique<EnemyController>(std::move(enemy));
        m_enemyControllers.push_back(std::move(controller));
      }
    }
  }

  // initialize healthpack controllers
  for (auto &hPack : m_hPacks) {
    DLOG("healthpack: " << hPack->serialize());

    auto ex = hPack->getXPos();
    auto ey = hPack->getYPos();
    nodes[ey * m_world.getCols() + ex].setFlag(3);

    unique_ptr<HealthpackController> controller =
        std::make_unique<HealthpackController>(std::move(hPack));
    m_healthPackControllers.push_back(std::move(controller));
  }
  // initialize protagonist controller
  unique_ptr<Protagonist> protagonistModel = m_world.getProtagonist();
  QObject::connect(protagonistModel.get(), &Protagonist::energyChanged, this,
                   &Game::playerEnergyChanged);
  QObject::connect(protagonistModel.get(), &Protagonist::healthChanged, this,
                   &Game::playerHealthChanged);
  DLOG("protagonist: " << protagonistModel->serialize());
  m_protagonistController =
      std::make_unique<ProtagonistController>(std::move(protagonistModel));

  // defining the controllers struct
  controllers controllers = {.enemies = m_enemyControllers,
                             .pEnemies = m_pEnemyControllers,
                             .xEnemies = m_xEnemyControllers,
                             .hPacks = m_healthPackControllers,
                             .protagonist = m_protagonistController,
                             .astar = m_astar,
                             .poisonedTiles = poisonedTiles};

  // initialize command factory
  m_cmdFactory = std::make_unique<CommandFactory>(controllers, *this);


  // Initializes the graphics
  m_gView =
      std::make_unique<GraphicsView>(m_parent, this, &m_world, &controllers);

  QObject::connect(m_protagonistController->getModel().get(),
                   &Protagonist::healthChanged, m_tView.get(),
                   &TextView::playerHealthChanged);
  QObject::connect(m_protagonistController->getModel().get(),
                   &Protagonist::energyChanged, m_tView.get(),
                   &TextView::playerEnergyChanged);
  QObject::connect(m_heuristicSlider, &QSlider::valueChanged, m_astar.get(),
                   &Astar::heuristicChanged);
  QObject::connect(m_pathSlider, &QSlider::valueChanged, m_astar.get(),
                   &Astar::pathWeightChanged);

  m_tView = std::make_unique<TextView>(*m_parent, m_world, controllers, m_tiles, m_cmdFactory);
  m_tView->update();

  QObject::connect(m_protagonistController->getModel().get(), &Protagonist::healthChanged, m_tView.get(), &TextView::playerHealthChanged);
  QObject::connect(m_protagonistController->getModel().get(), &Protagonist::energyChanged, m_tView.get(), &TextView::playerEnergyChanged);


  // Default view = graphicView
  m_defaultView = true;
  m_tView->hide();
  m_gView->show();



  // TODO momentary solution to click protagonist
  pathToPoint(QPoint(0, 0));

  // start game timer
  DLOG("Starting the timer - gameInit");
  m_refreshTimer->start(m_refreshTime);
}

void Game::switchView() {
  if (!m_defaultView) {
    m_gView->show();
    m_tView->hide();
  } else {
    m_gView->hide();
    m_tView->show();
  }
  m_defaultView = !m_defaultView;
}

void Game::showGraphics() {
  m_gView->show();
  m_tView->hide();
}

void Game::showText() {
  m_gView->hide();
  m_tView->show();
}

// only use one timer so everything is synchronized
void Game::updateGame() {
    DLOG("Timer overflows");
  // stop timer for uninterrupted executions
  m_refreshTimer->stop();

  m_tView->update();

  // this solution is to have poisontimer synced with refreshTimer
  // checkIfPoisened every 20x refreshTime
  if (m_iter == 20) {
    checkIfPoisened();
    moveXEnemies();
    m_iter = 0;
  }
  m_iter++;

  // moveProtagonist every m_refreshTime
  moveProtagonist();

  // check if all enemies are defaeted
  if (countAliveEnemies() <= 0) {
    win();
    return;
  }

  // move xEnemies every 10x refreshTime
  if (m_iter == 10 || m_iter == 20) {
    moveXEnemies();
  }

  // restart timer
  DLOG("Restarting timer - updateGame");
  m_refreshTimer->start(m_refreshTime);
}

void Game::moveProtagonist() {
  // Astar takes priority over key press, meaning we cannot change path we
  // clicked

  // if there are steps to be executed from m_sol
  if (moving()) {
    moveTo(m_sol[m_solIndex]->getX(), m_sol[m_solIndex]->getY());
    // check if all enemies are defaeted
    if (m_countLiveEnemies <= 0) {
      return;
    }
    x = m_sol[m_solIndex]->getX();
    y = m_sol[m_solIndex]->getY();
    m_solIndex++;
    if (m_solIndex == (int)m_sol.size()) {
      DLOG("Resetting map - max index reached")
      m_astar->resetMap();
    }
  }

  // if there was a key pressed
  else if (m_key != -1) {
    keyMove(m_key);
    // set back to default 0
    m_key = -1;
  }

  // if autoplay enabled, call pathToPoint on its own
  else if (!moving() && m_autoplay) {
    autoMove();
  }

  // even if not input, still check to see if collision occurs
  else {
    // TODO discuss whether its worth it
    //    moveTo(m_protagonistController->getModel()->getXPos(),
    //           m_protagonistController->getModel()->getYPos(),
    //           m_protagonistController->getModel()->getXPos(),
    //           m_protagonistController->getModel()->getYPos());
  }
}

void Game::pathToPoint(QPoint position) {
  // check if there are steps being executed
  // if so, dont accept new clicks
  std::unique_ptr<Command> c = m_cmdFactory->createCommand(
      "goto", {std::to_string(position.x()), std::to_string(position.y())});
  c->execute();
  return;
}

void Game::keyMove(int key) {
  int x = m_protagonistController->getModel()->getXPos();
  int y = m_protagonistController->getModel()->getYPos();
  int oldX = x;
  int oldY = y;
  if (key == Qt::Key_Left) {
    x = oldX - 1;
  } else if (key == Qt::Key_Right) {
    x = oldX + 1;
  } else if (key == Qt::Key_Up) {
    y = oldY - 1;
  } else if (key == Qt::Key_Down) {
    y = oldY + 1;
  }
  moveTo(x, y);
}

void Game::moveTo(int x, int y) {
    DLOG("calling moveTo");
  // check if movement not out of bounds
  std::unique_ptr<Command> command = m_cmdFactory->createCommand(
      "moveTo", {std::to_string(x), std::to_string(y)});
  command->execute();
}

void Game::checkIfPoisened() {
  // std::cout << "checkIfPoisened !" << std::endl;
  int index =
      m_protagonistController->getModel()->getXPos() +
      m_protagonistController->getModel()->getYPos() * m_world.getCols();

  for (poisened_tile_t &poisenedTile : poisonedTiles) {

    if (!poisenedTile.active_t) {
      continue;
    };

    // if enemy is defeated
    if (poisenedTile.pEnemy_t->getDefeated()) {
      // set opacity to 0
      poisenedTile.poisonedSquare_t->setOpacity(0);
      // set tile to inactive
      poisenedTile.active_t = false;
      continue;
    }

    // if poison has weared off, set enemy as dead
    if (poisenedTile.pEnemy_t->getPoisonLevel() <= 0) {
      poisenedTile.pEnemy_t->setDefeated(true);
      continue;
    }

    // set opacity to new poison value
    poisenedTile.poisonedSquare_t->setOpacity(
        poisenedTile.pEnemy_t->getPoisonLevel() / 100);

    // if protagonist is in poisoned tile i.e. same index
    // and if we didnt just hit
    if (index == poisenedTile.index_t) {
      DLOG("Protagonist poisened !");
      DLOG("health before poison: "
           << m_protagonistController->getModel()->getHealth())

      // poison protagonist
      m_protagonistController->poison(poisenedTile.pEnemy_t->getPoisonLevel() /
                                      m_difficultyFactor);
      DLOG("health after poison: "
           << m_protagonistController->getModel()->getHealth());

      // check if dead
      if (m_protagonistController->getModel()->getHealth() == 0) {
        lose();
      }
    }
  }
}

void Game::moveXEnemies() {
  for (std::unique_ptr<XEnemyController> &xEnemyC : m_xEnemyControllers) {
    // only move if not defeated
    if (xEnemyC->getModel()->getDefeated()) {
      continue;
    }

    // rand() % 3 -1 gives either -1, 0 or +1
    int xRand = rand() % 3 - 1;
    int yRand = rand() % 3 - 1;
    int x = xEnemyC->getModel()->getXPos() + xRand;
    int y = xEnemyC->getModel()->getYPos() + yRand;

    // check and correct if movement out of bounds
    if ((x < 0) || (x > m_world.getCols() - 1)) {
      x = xEnemyC->getModel()->getXPos() - xRand;
    }
    if ((y < 0) || (y > m_world.getRows() - 1)) {
      y = xEnemyC->getModel()->getYPos() - yRand;
    }

    // check if tile impassable
    int index = x + y * m_world.getCols();
    float tileValue = m_tiles[index]->getValue();
    if (tileValue != std::numeric_limits<float>::max()) {
      xEnemyC->move(x, y);
    }
  }
}

void Game::autoMove() {
  // source
  int sx = m_protagonistController->getModel()->getXPos();
  int sy = m_protagonistController->getModel()->getYPos();
  int health = m_protagonistController->getModel()->getHealth();

  // select nearest enemy
  float minCostToEnemy = std::numeric_limits<float>::max();
  int nearestEnemyIndex = -1;
  int enemyStrength = 0;
  // loop over enemies
  for (auto &enemyC : m_enemyControllers) {
    // only consider live enemies
    if (!enemyC->getModel()->getDefeated()) {
      // find Astar solution
      vector<Node *> sol = m_astar->findPath(
          sx, sy, enemyC->getModel()->getXPos(), enemyC->getModel()->getYPos());
      std::reverse(sol.begin(), sol.end());
      // store min cost and nearest enemy
      float cost = sol.back()->getCost();
      if (cost < minCostToEnemy) {
        minCostToEnemy = cost;
        nearestEnemyIndex = enemyC->getModel()->getXPos() +
                            enemyC->getModel()->getYPos() * m_world.getCols();
        enemyStrength = enemyC->getModel()->getValue();
      }
      // reset map
      m_astar->resetMap();
    }
  }
  // loop over penemies
  for (auto &enemyC : m_pEnemyControllers) {
    // only consider penemies not dying
    if (!enemyC->isDying()) {
      // find Astar solution
      vector<Node *> sol = m_astar->findPath(
          sx, sy, enemyC->getModel()->getXPos(), enemyC->getModel()->getYPos());
      std::reverse(sol.begin(), sol.end());
      // store min cost and nearest enemy
      float cost = sol.back()->getCost();
      if (cost < minCostToEnemy) {
        minCostToEnemy = cost;
        nearestEnemyIndex = enemyC->getModel()->getXPos() +
                            enemyC->getModel()->getYPos() * m_world.getCols();
        enemyStrength = enemyC->getModel()->getValue();
      }
      // reset map
      m_astar->resetMap();
    }
  }
  // loop over xenemies
  for (auto &enemyC : m_xEnemyControllers) {
    // only consider live enemies
    if (!enemyC->getModel()->getDefeated()) {
      // find Astar solution
      vector<Node *> sol = m_astar->findPath(
          sx, sy, enemyC->getModel()->getXPos(), enemyC->getModel()->getYPos());
      std::reverse(sol.begin(), sol.end());
      // store min cost and nearest enemy
      float cost = sol.back()->getCost();
      if (cost < minCostToEnemy) {
        minCostToEnemy = cost;
        nearestEnemyIndex = enemyC->getModel()->getXPos() +
                            enemyC->getModel()->getYPos() * m_world.getCols();
        enemyStrength = enemyC->getModel()->getValue();
      }
      // reset map
      m_astar->resetMap();
    }
  }
  // if protagonist health is lower than enemy
  if (health < enemyStrength) {
    // select nearest hPack
    int minCostToHPack = std::numeric_limits<int>::max();
    int nearestHPackIndex = -1;
    // loop over hPacks
    for (auto &hPackC : m_healthPackControllers) {
      // only consider full hPacks
      if (!hPackC->isEmpty()) {
        // find Astar solution
        vector<Node *> sol =
            m_astar->findPath(sx, sy, hPackC->getModel()->getXPos(),
                              hPackC->getModel()->getYPos());
        std::reverse(sol.begin(), sol.end());
        // store min cost and nearest enemy
        float cost = sol.back()->getCost();
        if (cost < minCostToHPack) {
          minCostToHPack = cost;
          nearestHPackIndex = hPackC->getModel()->getXPos() +
                              hPackC->getModel()->getYPos() * m_world.getCols();
        }
        // reset map
        m_astar->resetMap();
      }
    }
    if (nearestHPackIndex == -1) {
      lose();
    } else {
      // move to hPack position
      pathToPoint(QPoint(m_tiles[nearestHPackIndex]->getXPos(),
                         m_tiles[nearestHPackIndex]->getYPos()));
    }
  } else {
    // move to enemy position
    pathToPoint(QPoint(m_tiles[nearestEnemyIndex]->getXPos(),
                       m_tiles[nearestEnemyIndex]->getYPos()));
  }
}

void Game::win() {
  QMessageBox::information(m_parent, "Winner!", "You win!");
  endGame();
}

void Game::lose() {
  DLOG("Losing game");
  QMessageBox::information(m_parent, "Loser!", "You lose!");
  DLOG("Ending the game...");
  endGame();
}

void Game::endGame() {
    DLOG("Stopping timer");
  m_refreshTimer->stop();
  while(m_refreshTimer->isActive()) ;
  DLOG("Resetting the data");
  resetData();
  DLOG("Hiding the ui");
  hideUI();
  DLOG("Hiding the views");
  m_gView->hide();
  m_tView->hide();
  // show amazing art
  DLOG("Show amazing art");
  m_welcomeLabel->show();
}

void Game::showUI() {
  m_welcomeLabel->hide();
  m_file_button->hide();
  m_autoplay_button->show();
  m_heuristic_text->show();
  m_heuristicSlider->show();
  m_path_text->show();
  m_pathSlider->show();
  m_difficulty_text->show();
  m_easyBtn->show();
  m_mediumBtn->show();
  m_hardBtn->show();
  m_refresh_text->show();
  m_refreshSlider->show();
  m_zoom_text->show();
  m_zoomSlider->show();
  m_view_button->show();
}
void Game::pathWeightChanged(float newPathWeight) { pathW = newPathWeight; }
void Game::scaleChanged(float newScale) {
  int diff = prev_slider_value - newScale;
  prev_slider_value = newScale;
  std::cout << diff << std::endl;
  if (diff > 0) {
    m_gView->scaleViews(0.5);
    m_tView->setScale(0.5);
  } else {
    m_gView->scaleViews(2);
    m_tView->setScale(2);
  }
}

void Game::hideUI() {
  m_welcomeLabel->show();
  m_file_button->show();
  m_autoplay_button->hide();
  m_heuristic_text->hide();
  m_heuristicSlider->hide();
  m_path_text->hide();
  m_pathSlider->hide();
  m_difficulty_text->hide();
  m_easyBtn->hide();
  m_mediumBtn->hide();
  m_hardBtn->hide();
  m_refresh_text->hide();
  m_refreshSlider->hide();
  m_zoom_text->hide();
  m_zoomSlider->hide();
  m_view_button->hide();
}

// reset the controllers, otherwise the next new map will add characters to the
// previous one and you will get a seg fault
void Game::resetData() {
  m_protagonistController->resetProtagonist();
  m_enemyControllers.clear();
  m_pEnemyControllers.clear();
  m_xEnemyControllers.clear();
  m_healthPackControllers.clear();
  poisonedTiles.clear();
}

int Game::countAliveEnemies() {
  int alive = 0;
  for (auto &enemyC : m_enemyControllers) {
    if (!enemyC->getModel()->getDefeated())
      alive++;
  }
  for (auto &enemyC : m_pEnemyControllers) {
    if (!enemyC->getModel()->getDefeated())
      alive++;
  }
  for (auto &enemyC : m_xEnemyControllers) {
    if (!enemyC->getModel()->getDefeated())
      alive++;
  }
  return alive;
}

void Game::playerEnergyChanged(int e) {
  if (e == 0) {
    lose();
  }
}
void Game::playerHealthChanged(int h) {
  if (h <= 0) {
    lose();
  }
}

void Game::drawPastTile(int x, int y) { m_gView->drawPastTile(x, y); }

void Game::drawPoisonnedTile(int px, int py, PEnemy &pEnemy) {
  // TODO: Move to a separate function in game.cpp
  //  draw poisoned tiles
  QGraphicsRectItem *poisonedSquare = m_gView->drawPoisonedTile(px, py);

  // set opacity to poison value
  poisonedSquare->setOpacity(pEnemy.getPoisonLevel());

  // define poisened_tile_t
  poisened_tile_t poisonedTile_t = {.index_t = px + py * m_world.getCols(),
                                    .pEnemy_t = &pEnemy,
                                    .poisonedSquare_t = poisonedSquare,
                                    .active_t = true};

  // push poisonedTile_t to list
  poisonedTiles.push_back(poisonedTile_t);
}

void Game::stopUpdateTimer() { m_refreshTimer->stop(); }
void Game::startUpdateTimer() { m_refreshTimer->start(m_refreshTime); }

void Game::heuristicChanged(float newHeuristic) {
  std::cout << newHeuristic / 10 << std::endl;
  heuristicW = newHeuristic / 10;
}


void Game::difficultyChanged() {
  if (m_easyBtn->isChecked()) {
    m_mediumBtn->setChecked(false);
    m_hardBtn->setChecked(false);
    m_difficultyFactor = 3;
  }
  if (m_mediumBtn->isChecked()) {
    m_easyBtn->setChecked(false);
    m_hardBtn->setChecked(false);
    m_difficultyFactor = 2;
  }
  if (m_hardBtn->isChecked()) {
    m_easyBtn->setChecked(false);
    m_mediumBtn->setChecked(false);
    m_difficultyFactor = 1;
  }
}

void Game::addPathToQueue(vector<Node *> newPath) {
  if (m_solIndex >= (int)m_sol.size() - 1) {
    m_sol = newPath;
    m_solIndex = 0;
  }
};


void Game::textCommandFeedback(QString val){
    m_tView->commandResult(val);
}
