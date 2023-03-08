#include "protagonist_controller.h"

ProtagonistController::ProtagonistController(std::unique_ptr<Protagonist> model)
    : model{std::move(model)}, m_tView{std::make_unique<ProtagonistTextView>()} {

    // define view
    view = std::make_unique<ProtagonistGraphicsView>(":/images/alive_homer.png");

    // protagonist timer
    timer = std::make_unique<QTimer>(this);
    timer->setSingleShot(true);
    connect(timer.get(), SIGNAL(timeout()), this, SLOT(setDefaultImage()));
}

unique_ptr<Protagonist> &ProtagonistController::getModel() {
  return this->model;
}

unique_ptr<ProtagonistGraphicsView> &ProtagonistController::getView() {
    return this->view;
}

void ProtagonistController::moveTo(int x, int y)
{
    // update model position
    model->setPos(x, y);

    // update view position
    view->setX(x * m_tileSize);
    view->setY(y * m_tileSize);

    // change image for 300 miliseconds before going to default
    view->setPixmap(QPixmap(":/images/moving_homer.png"));
    timer->start(300);
}

void ProtagonistController::loseEnergy(float energy){
    // loose energy
    if(model->getEnergy()-energy <= 0) {
        // exhausted
        model->setEnergy(0);
        // change image forever
        view->setPixmap(QPixmap(":/images/dead_homer.png"));
        m_tView->setDead();
        timer->stop();
    }
    else {
        // survive
        model->setEnergy(model->getEnergy() - energy);
    }
}

void ProtagonistController::heal(float value){
    // update health
    if(model->getHealth() + value < 100.0f) {
        model->setHealth(model->getHealth() + value);
    }
    else {
        model->setHealth(100.0f);
    }
    // change image for 1 second before going to default
    view->setPixmap(QPixmap(":/images/healing_homer.png"));
    m_tView->setHealing();
    timer->start(1000);
}

void ProtagonistController::fight(float damage)
{
    // temporarily change image
    view->setPixmap(QPixmap(":/images/fight_homer.png"));
    m_tView->setDamage();

    // lose health
    if(model->getHealth()-damage <= 0) {
        // lose
        model->setHealth(0);
        view->setPixmap(QPixmap(":/images/dead_homer.png"));
        m_tView->setDead();
        timer->stop();
    }
    else {
        // win
        model->setHealth(model->getHealth() - damage);
        model->setEnergy(100.0f);
        view->setPixmap(QPixmap(":/images/won_homer.png"));
    }
}

void ProtagonistController::poison(float damage)
{
    // temporarily change image
    view->setPixmap(QPixmap(":/images/poisened_homer.png"));
    m_tView->setPoison();
    timer->start(1000);

    // lose health
    if(model->getHealth()-damage <= 0) {
        // lose
        model->setHealth(0);
        view->setPixmap(QPixmap(":/images/dead_homer.png"));
        m_tView->setDead();
        timer->stop();
    } else {
        // win
        model->setHealth(model->getHealth() - damage);
    }
}

void ProtagonistController::setDefaultImage()
{
    view->setPixmap(QPixmap(":/images/alive_homer.png"));
    m_tView->setDefault();
}

void ProtagonistController::resetProtagonist()
{
    model->setPos(0,0);
    view->setPos(0,0);
    model->setHealth(100.0f);
    model->setEnergy(100.0f);
}


