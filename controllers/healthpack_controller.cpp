#include "healthpack_controller.h"
#include "world.h"

HealthpackController::HealthpackController(std::unique_ptr<Tile> model)
    : model{std::move(model)}, m_textView{std::make_unique<HealthpackTextView>()} {
  view = std::make_unique<HealthpackGraphicsView>(":/images/full_duff_beer.png");
}

std::unique_ptr<Tile> &HealthpackController::getModel() { return this->model; }

std::unique_ptr<HealthpackTextView> &HealthpackController::getTextView() {
  return m_textView;
}

unique_ptr<HealthpackGraphicsView> &HealthpackController::getView() {
  return this->view;
}

void HealthpackController::used() {
  // set to empty so it cant be reused
  empty = true;
  // change animation
  view->setPixmap(QPixmap(":/images/empty_duff_beer.png"));
  m_textView->empty();
  view->getTextValue()->hide();
}

bool HealthpackController::isEmpty() const { return empty; }
