#ifndef HEALTHPACK_CONTROLLER_H
#define HEALTHPACK_CONTROLLER_H

#include "world.h"

#include "views/graphics/healthpack_graphics_view.h"
#include "views/text/healthpack_text_view.h"

using std::unique_ptr;

class HealthpackController {
public:
  HealthpackController() = delete;
  HealthpackController(std::unique_ptr<Tile> model);

  std::unique_ptr<Tile> &getModel();
  unique_ptr<HealthpackGraphicsView> &getView();
  std::unique_ptr<HealthpackTextView> & getTextView();

  void used();

  bool isEmpty() const;

protected:
  std::unique_ptr<Tile> model;
  unique_ptr<HealthpackGraphicsView> view;
  std::unique_ptr<HealthpackTextView> m_textView;

private:
  bool empty = false;
};

#endif // HEALTHPACK_CONTROLLER_H
