#ifndef PROTAGONIST_CONTROLLER_H
#define PROTAGONIST_CONTROLLER_H

#include "world.h"
#include <QObject>
#include <QTimer>

#include <unistd.h>

#include "views/graphics/protagonist_graphics_view.h"
#include "views/text/protagonist_textview.h"

using std::unique_ptr;

class ProtagonistController : public QObject {
    Q_OBJECT

public:
  ProtagonistController() = delete;
  ProtagonistController(unique_ptr<Protagonist> model);

  unique_ptr<Protagonist> &getModel();
  unique_ptr<ProtagonistGraphicsView> &getView();
  unique_ptr<ProtagonistTextView> &getTextView(){return m_tView;}

  void moveTo(int x, int y);

  void heal(float value);
  void fight(float damage);
  void poison(float damage);
  void loseEnergy(float energy);
  void loseHealth(float damage);

  void setTileSize(int newTileSize) {m_tileSize = newTileSize;};

  void resetProtagonist();

public slots:
  void setDefaultImage();

private:
  unique_ptr<Protagonist> model;
  unique_ptr<ProtagonistGraphicsView> view;
  unique_ptr<ProtagonistTextView> m_tView;

  World * m_world;

  unique_ptr<QTimer> timer;

  int m_tileSize;

};

#endif // PROTAGONIST_CONTROLLER_H
