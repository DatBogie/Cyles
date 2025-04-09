#include "theme.h"
#include "cylesutils.h"
#include <QString>

Theme::Theme() {}

Theme::Theme(QString name, bool dark, std::vector<QColor> colors) {
    Name = name;
    IsDark = dark;
    ButtonColor = colors[0];
    TextInputColor = colors[1];
    BackgroundColor = colors[2];
    AccentColor = colors[3];
}

QString Theme::toQString() {
    return "QWidget { background-color: "+CylesUtils::QColorToQString(BackgroundColor)+"; color: "+(CylesUtils::IsQColorDark(BackgroundColor)? "white":"black" )+"; selection-background-color: "+CylesUtils::QColorToQString(AccentColor)+"; }"+
           "QPushButton, QComboBox { padding: 2px; border-radius: 6px; border: 2px solid "+CylesUtils::QColorToQString(ButtonColor.lighter(10*(CylesUtils::IsQColorDark(ButtonColor)? 1 : -1)))+"; background-color: "+CylesUtils::QColorToQString(ButtonColor)+"; color: "+(CylesUtils::IsQColorDark(ButtonColor)? "white" : "black")+"; }"+
           "QPushButton:hover, QComboBox:hover { border: 2px solid "+CylesUtils::QColorToQString(AccentColor)+"; background-color: "+CylesUtils::QColorToQString(ButtonColor.lighter(15))+" }"+
           "QPushButton:pressed, QComboBox:pressed { border: 2px solid "+CylesUtils::QColorToQString(AccentColor)+"; background-color: "+CylesUtils::QColorToQString(ButtonColor.lighter(-10))+"; }"+
           "QComboBox::drop-down { background: transparent; }"+
           "QLineEdit, QTextEdit { background-color: "+CylesUtils::QColorToQString(TextInputColor)+"; color: "+(CylesUtils::IsQColorDark(TextInputColor)? "white":"black" )+"; }";
}
