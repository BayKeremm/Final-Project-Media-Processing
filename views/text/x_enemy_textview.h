#ifndef XENEMYTEXTVIEW_H
#define XENEMYTEXTVIEW_H

#include <QString>
#include "views/text/enemy_text_view.h"

#define ALIVE_TEXT " <span class=\"text\" style=\"color:#D00\">X</span>"
#define DEAD_TEXT " <span class=\"text\" style=\"color:#D00\"><del>x</del></span>"

class XEnemyTextView : public EnemyTextView
{
public:
    XEnemyTextView(){m_toDisplay = ALIVE_TEXT;}
    void setDead(){m_toDisplay = DEAD_TEXT;}
};

#endif // XENEMYTEXTVIEW_H
