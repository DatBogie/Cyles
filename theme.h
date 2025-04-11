#ifndef THEME_H
#define THEME_H

#include <QString>
#include <QColor>
#include <vector>
#include <QStyle>
#include <QProxyStyle>
#include <QStyleOptionButton>
#include <QStyleOptionComboBox>
#include <QPalette>
#include <QPainterPath>
#include <QPainter>
#include <QPen>

#pragma once
class ThemeStyle;

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
    QString toQString();
    ThemeStyle* toThemeStyle();
};

class ThemeStyle : public QProxyStyle
{
public:
    ThemeStyle(const Theme& theme, QStyle* baseStyle = nullptr) : QProxyStyle(baseStyle), theme(theme), baseStyle(baseStyle) {}

    void drawControl(ControlElement element, const QStyleOption* option, QPainter* painter, const QWidget* widget = nullptr) const override;
private:
    const Theme theme;
    const QStyle* baseStyle;
};

#endif // THEME_H
