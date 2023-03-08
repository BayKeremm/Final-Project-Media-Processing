#ifndef PROTAGONISTTEXTVIEW_H
#define PROTAGONISTTEXTVIEW_H

#include <QString>


#define DEFAULT_TEXT " <b class=\"text\" style=\"color:#5DD;\">P</b>"
#define DAMAGE_TEXT " <b class=\"text\" style=\"color:#D00;\">P</b>"
#define POISON_TEXT " <b class=\"text\" style=\"color:#D0D;\">P</b>"
#define HEALING_TEXT " <b class=\"text\" style=\"color:#0D0;\">P</b>"
#define DEAD_TEXT " <b class=\"text\" style=\"color:#000;\">p</b>"


class ProtagonistTextView
{
private:
    QString m_toDisplay = DEFAULT_TEXT;
public:
    ProtagonistTextView();
    void setDefault(){m_toDisplay = DEFAULT_TEXT;}
    void setDamage(){m_toDisplay = DAMAGE_TEXT;}
    void setPoison(){m_toDisplay = POISON_TEXT;}
    void setHealing(){m_toDisplay = HEALING_TEXT;}
    void setDead(){m_toDisplay = DEAD_TEXT;}
    QString print(){return m_toDisplay;}
};

#endif // PROTAGONISTTEXTVIEW_H
