#ifndef ENEMYTEXTVIEW_H
#define ENEMYTEXTVIEW_H

#include <QString>

#define TEXT_ALIVE " <span class=\"text\" style=\"color:#D00\">E</span>"
#define TEXT_DEAD " <span class=\"text\" style=\"color:#D00\">e</span>"

class EnemyTextView
{
protected:
    QString m_toDisplay = TEXT_ALIVE;
public:
    EnemyTextView();
    virtual void setDead(){m_toDisplay = TEXT_DEAD;}
    QString print(){return m_toDisplay;}
};

#endif // ENEMYTEXTVIEW_H
