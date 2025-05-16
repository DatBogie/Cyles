#ifndef PREFWINDOW_H
#define PREFWINDOW_H

#include "mainwindow.h"
#include <QWidget>
#include <QComboBox>
#include <QCheckBox>

#pragma once
class MainWindow;

class PrefWindow : public QWidget
{
    Q_OBJECT
public:
    explicit PrefWindow(MainWindow* win);
    void toggle();
    MainWindow* win;
private slots:
    void updateStyle(int index);
    void toggleIconColor(Qt::CheckState state);
    // void updateTheme(int index);
    // void createTheme();
    // void deleteTheme();
private:
    QComboBox* styleBox;
    QCheckBox* useDarkIcons;
    // QComboBox* themeBox;
    // void themesUpdated();
};

#endif // PREFWINDOW_H
