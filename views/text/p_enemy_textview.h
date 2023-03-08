#ifndef PENEMYTEXTVIEW_H
#define PENEMYTEXTVIEW_H

#include <QString>
#include "views/text/enemy_text_view.h"

#define ALIVE_TEXT " <span class=\"text\" style=\"color:#D0D\">E</span>"
#define DEAD_TEXT " <span class=\"text\" style=\"color:#D0D\">e</span>"

class PEnemyTextView : public EnemyTextView
{
public:
    PEnemyTextView(){m_toDisplay = ALIVE_TEXT;}
    void setDead()override{m_toDisplay = DEAD_TEXT;}
};

#endif // PENEMYTEXTVIEW_H
