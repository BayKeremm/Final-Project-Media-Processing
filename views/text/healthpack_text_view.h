#ifndef HEALTHPACKTEXTVIEW_H
#define HEALTHPACKTEXTVIEW_H

#include <QString>

#define FULL " <span class=\"text\" style=\"color:#0A0;\"><b>H</b></span>"
#define EMPTY " <span class=\"text\" style=\"color:#050;\"><b>h</b></span>"

class HealthpackTextView
{
private:
    QString m_textView = FULL;
public:
    HealthpackTextView();
    void empty(){m_textView = EMPTY;}
    QString print();
};

#endif // HEALTHPACKTEXTVIEW_H
