#include "theme.h"
#include "cylesutils.h"
#include <QString>
#include <QStyle>
#include <QProxyStyle>
#include <QStyleFactory>
#include <QPainter>
#include <QPainterPath>
#include <QPen>
#include <QColor>
#include <QSize>
#include <QRect>
#include <iostream>
#include <QStyleOptionButton>
#include <QStyleOptionViewItem>

Theme::Theme() {}

Theme::Theme(QString name, bool dark, std::vector<QColor> colors) {
    Name = name;
    IsDark = dark;
    ButtonColor = colors[0];
    TextInputColor = colors[1];
    BackgroundColor = colors[2];
    AccentColor = colors[3];
}

ThemeStyle* Theme::toThemeStyle() {
    return new ThemeStyle(*this,QStyleFactory::create("Fusion"));
}

QString Theme::toQString() {
    return "QWidget { background-color: "+CylesUtils::QColorToQString(BackgroundColor)+"; color: "+(CylesUtils::IsQColorDark(BackgroundColor)? "white":"black" )+"; selection-background-color: "+CylesUtils::QColorToQString(AccentColor)+"; }"+
           "QPushButton, QComboBox { padding: 2px; border-radius: 6px; border: 2px solid "+CylesUtils::QColorToQString(ButtonColor.lighter(10*(CylesUtils::IsQColorDark(ButtonColor)? 1 : -1)))+"; background-color: "+CylesUtils::QColorToQString(ButtonColor)+"; color: "+(CylesUtils::IsQColorDark(ButtonColor)? "white" : "black")+"; }"+
           "QPushButton:hover, QComboBox:hover { border: 2px solid "+CylesUtils::QColorToQString(AccentColor)+"; background-color: "+CylesUtils::QColorToQString(ButtonColor.lighter(15))+" }"+
           "QPushButton:pressed, QComboBox:pressed { border: 2px solid "+CylesUtils::QColorToQString(AccentColor)+"; background-color: "+CylesUtils::QColorToQString(ButtonColor.lighter(-10))+"; }"+
           "QComboBox::drop-down { background: transparent; }"+
           "QLineEdit, QTextEdit { background-color: "+CylesUtils::QColorToQString(TextInputColor)+"; color: "+(CylesUtils::IsQColorDark(TextInputColor)? "white":"black" )+"; }";
}

void ThemeStyle::drawControl(ControlElement element, const QStyleOption* option, QPainter* painter, const QWidget* widget) const {
    if (element == CE_PushButton) {
        QStyleOptionButton btn(*qstyleoption_cast<const QStyleOptionButton*>(option));
        btn.palette.setColor(QPalette::Button,theme.ButtonColor);
        btn.palette.setColor(QPalette::ButtonText,theme.ButtonColor.lightness() >= 128? QColor(Qt::black) : QColor(Qt::white));
        QPainterPath path;
        path.addRoundedRect(btn.rect.adjusted(2,2,-2,-2), 6, 6);
        painter->save();
        painter->setRenderHint(QPainter::Antialiasing);

        QColor bgColor = theme.ButtonColor;
        QColor borderColor = CylesUtils::IsQColorDark(theme.ButtonColor)? CylesUtils::LightenQColor(theme.ButtonColor,20) : CylesUtils::DarkenQColor(theme.ButtonColor,40);
        if (btn.state & State_Sunken || btn.state & State_On) {
            bgColor = CylesUtils::DarkenQColor(theme.ButtonColor,10);
            borderColor = theme.AccentColor;
        } else if (btn.state & State_MouseOver) {
            bgColor = CylesUtils::LightenQColor(theme.ButtonColor,10);
            borderColor = theme.AccentColor;
        }

        // bg
        painter->fillPath(path, bgColor);

        // Border
        QPen pen(borderColor, 2);
        painter->setPen(pen);
        painter->drawPath(path);

        // Icon
        if (!btn.icon.isNull()) {
            QSize iconSize = btn.iconSize;
            QRect iconRect = subElementRect(SE_PushButtonContents, &btn, widget);

            // Align icon to left or center
            iconRect.setSize(iconSize);
            iconRect.moveCenter(btn.rect.center());

            // Optional: move it slightly left/right
            iconRect.moveLeft(btn.rect.left() + 6);

            btn.icon.paint(painter, iconRect, Qt::AlignCenter, btn.state & State_Enabled ? QIcon::Normal : QIcon::Disabled);
        }

        // Text
        painter->setPen(QColor(CylesUtils::IsQColorDark(theme.ButtonColor)? Qt::white : Qt::black));
        painter->drawText(btn.rect, Qt::AlignCenter, btn.text);

        painter->restore();
    } else if (element == CE_ItemViewItem) {
        const QStyleOptionViewItem* viewOpt = qstyleoption_cast<const QStyleOptionViewItem*>(option);
        if (!viewOpt) return;

        QStyleOptionViewItem opt(*viewOpt);
        painter->save();

        QRect rect = opt.rect;
        QColor bg = theme.BackgroundColor;
        QColor text = CylesUtils::IsQColorDark(bg) ? Qt::white : Qt::black;

        if (opt.state & State_Selected) {
            bg = theme.AccentColor;
            text = CylesUtils::IsQColorDark(bg) ? Qt::white : Qt::black;
        } else if (opt.state & State_MouseOver) {
            bg = CylesUtils::LightenQColor(bg, 5);
        }

        painter->setBrush(bg);
        painter->setPen(Qt::NoPen);
        painter->drawRect(rect);

        if (!opt.icon.isNull()) {
            QSize iconSize = QSize(16, 16);  // Default size if iconSize is not specified
            QRect iconRect = rect;
            iconRect.setSize(iconSize);
            iconRect.moveLeft(rect.left() + 3);  // Position the icon with a margin on the left

            // Optional: Adjust the alignment of the icon (centered, top, bottom, etc)
            opt.icon.paint(painter, iconRect, Qt::AlignCenter, opt.state & State_Enabled ? QIcon::Normal : QIcon::Disabled);
        }

        // Draw text (or icon, etc)
        painter->setPen(text);
        painter->drawText(rect.adjusted(25, 0, -5, 0), Qt::AlignVCenter | Qt::AlignLeft, opt.text);

        painter->restore();
    } else {
        QProxyStyle::drawControl(element, option, painter, widget);
        return;
    }
}
