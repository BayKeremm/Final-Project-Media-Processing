#include "enemy_controller.h"
#include "views/graphics/enemy_graphics_view.h"

EnemyController::EnemyController(unique_ptr<Enemy> model, bool generateView)
    : model{std::move(model)} {
    if (generateView) {
      view = std::make_unique<EnemyGraphicsView>(":/images/alive_fat_tony.png");
      m_textView = std::make_unique<EnemyTextView>();
    }
  }

unique_ptr<Enemy> &EnemyController::getModel() { return this->model; }

unique_ptr<EnemyTextView> &EnemyController::getTextView() { return m_textView; }

unique_ptr<EnemyGraphicsView> &EnemyController::getView() { return this->view; }

void EnemyController::defeat() {
  model->setDefeated(true);
  // change animation
  view->setPixmap(QPixmap(":/images/dead_fat_tony.png"));
  m_textView->setDead();
  view->getTextValue()->hide();
}
