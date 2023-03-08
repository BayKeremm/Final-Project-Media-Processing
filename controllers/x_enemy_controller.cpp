#include "x_enemy_controller.h"
#include "views/graphics/x_enemy_graphics_view.h"
#include "views/text/x_enemy_textview.h"

XEnemyController::XEnemyController(std::unique_ptr<Enemy> model) : EnemyController(std::move(model), false){
    view = std::make_unique<XEnemyGraphicsView>(":/images/alive_sideshow_bob.png");
    m_textView = std::make_unique<XEnemyTextView>();

    timer = std::make_unique<QTimer>(this);
    timer->setSingleShot(true);
    connect(timer.get(), SIGNAL(timeout()), this, SLOT(setDefaultImage()));
}

void XEnemyController::defeat()
{
    model->setDefeated(true);
    view->setPixmap(QPixmap(":/images/dead_sideshow_bob.png"));
    m_textView->setDead();
    view->getTextValue()->hide();
}

void XEnemyController::move(int x, int y)
{
    // update model position
    model->setXPos(x);
    model->setYPos(y);

    // update view position
    view->setX(x * m_tileSize);
    view->setY(y * m_tileSize);

    // change textValue position
    view->getTextValue()->setPos(x * m_tileSize, y * m_tileSize -20);

    // change image for 300 miliseconds before going to default
    view->setPixmap(QPixmap(":/images/moving_sideshow_bob.png"));
    timer->start(300);
}

void XEnemyController::setDefaultImage()
{
    view->setPixmap(QPixmap(":/images/alive_sideshow_bob.png"));
}
