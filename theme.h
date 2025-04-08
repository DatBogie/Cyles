#ifndef THEME_H
#define THEME_H

#include <QString>
#include <QColor>
#include <vector>

class Theme
{
public:
    Theme();
    Theme(QString name, bool dark, std::vector<QColor> colors);
    QString Name;
    bool IsDark;
    QColor ButtonColor;
    QColor TextInputColor;
    QColor BackgroundColor;
    QColor AccentColor;
};

#endif // THEME_H
