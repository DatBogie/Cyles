// #ifndef THEMEBUILDER_H
// #define THEMEBUILDER_H

// #include <QWidget>
// #include <QLineEdit>
// #include <QCheckBox>
// #include <QJsonObject>
// #include <QColor>
// #include <QPushButton>
// #include <vector>
// #include <QTextEdit>
// #include "theme.h"

// #pragma once
// class Theme;

// class ThemeBuilder : public QWidget
// {
//     Q_OBJECT
// public:
//     explicit ThemeBuilder(QJsonObject* theme = nullptr);
// private:
//     QLineEdit* nameField = new QLineEdit("Untitled Theme");
//     QCheckBox* darkField = new QCheckBox("Dark Theme");
//     QPushButton* pickButtonColor = new QPushButton("Choose Button Color...");
//     QPushButton* pickTextInputColor = new QPushButton("Choose Text Input Color...");
//     QPushButton* pickBackgroundColor = new QPushButton("Choose Background Color...");
//     QPushButton* pickAccentColor = new QPushButton("Choose Accent Color...");
//     QTextEdit* cssInput = new QTextEdit();
//     QColor buttonColor;
//     QColor textInputColor;
//     QColor backgroundColor;
//     QColor accentColor;
//     std::vector<QColor*> colors = {&buttonColor,&textInputColor,&backgroundColor,&accentColor};
//     void Complete();
// private slots:
//     void updateColor(int key);
// signals:
//     void completed(Theme theme);
// };

// #endif // THEMEBUILDER_H
