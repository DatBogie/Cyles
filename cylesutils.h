#ifndef CYLESUTILS_H
#define CYLESUTILS_H

#include <string>
#include <vector>
#include <QString>
#include <QColor>
#include <QMap>
#include <QApplication>

#include "theme.h"

#pragma once
class Theme;

#include "cylessignals.h"

#pragma once
class CylesSignals;

class CylesUtils
{
public:
    static CylesSignals* Signals;
    static const std::string QStringVectorToStdString(std::vector<QString> x);
    static const std::string OS;
    static const QString QColorToQString(QColor clr);
    static const bool IsQColorDark(QColor clr);
    static const void ApplyTheme(QWidget* widget, Theme theme);
    static const void ApplyTheme(QWidget* widget);
    static const void ApplyTheme(QApplication* app, Theme theme);
    static const void ApplyTheme(QApplication* app);
    static QColor LightenQColor(QColor x, int amt) {
        return QColor(std::clamp(x.red()+amt,0,255),std::clamp(x.green()+amt,0,255),std::clamp(x.blue()+amt,0,255));
    }
    static QColor DarkenQColor(QColor x, int amt) {
        return LightenQColor(x, -amt);
    }
    static QString SystemStyle;
    static QString DefaultStyle;
    static QColor ButtonColor;
    static QColor TextInputColor;
    static QColor BackgroundColor;
    static QColor AccentColor;
    static std::vector<QColor*> colors;
    static QMap<QString, Theme> Themes;
    static QList<QString> ProtectedThemes;
    static QString CurrentTheme;
    // static const QString DefaultStyle = "";
};

#endif // CYLESUTILS_H
