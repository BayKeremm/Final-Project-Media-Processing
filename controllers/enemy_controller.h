#ifndef ENEMY_CONTROLLER_H
#define ENEMY_CONTROLLER_H

#include <QObject>

#include "world.h"

#include "views/graphics/enemy_graphics_view.h"
#include "views/text/enemy_text_view.h"

using std::unique_ptr;

class EnemyController: public QObject {
    Q_OBJECT
public:
  EnemyController() = delete;
  EnemyController(std::unique_ptr<Enemy> model, bool generateView = true);

  unique_ptr<Enemy> &getModel();
  unique_ptr<EnemyGraphicsView> &getView();
  unique_ptr<EnemyTextView> & getTextView();

  virtual void defeat();

protected:
  unique_ptr<Enemy> model;
  unique_ptr<EnemyGraphicsView> view;
  unique_ptr<EnemyTextView> m_textView;

};

#endif // ENEMY_CONTROLLER_H
