#ifndef PREFWINDOW_H
#define PREFWINDOW_H

#include "mainwindow.h"
#include <QWidget>
#include <QComboBox>

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
    void updateTheme(int index);
    void createTheme();
    void deleteTheme();
private:
    QComboBox* styleBox;
    QComboBox* themeBox;
    void themesUpdated();
};

#endif // PREFWINDOW_H
