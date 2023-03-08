#include "p_enemy_controller.h"
#include "views/graphics/p_enemy_graphics_view.h"
#include "views/text/p_enemy_textview.h"

PEnemyController::PEnemyController(std::unique_ptr<Enemy> model) : EnemyController(std::move(model), false){
    view = std::make_unique<PEnemyGraphicsView>(":/images/alive_lucille.png");
    m_textView = std::make_unique<PEnemyTextView>();
}

void PEnemyController::defeat()
{
    dying = true;
    view->setPixmap(QPixmap(":/images/dead_lucille.png"));
    m_textView->setDead();
}
