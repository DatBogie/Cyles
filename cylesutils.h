#ifndef CYLESUTILS_H
#define CYLESUTILS_H

#include <string>
#include <vector>
#include <QString>
#include <QColor>
#include <QMap>

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
    static QString SystemStyle;
    static QString DefaultStyle;
    static QColor ButtonColor;
    static QColor TextInputColor;
    static QColor BackgroundColor;
    static QColor AccentColor;
    static std::vector<QColor*> colors;
    static QMap<QString, Theme> Themes;
    static QList<QString> ProtectedThemes;
    // static const QString DefaultStyle = "";
};

#endif // CYLESUTILS_H
