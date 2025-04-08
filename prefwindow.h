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
    explicit PrefWindow(MainWindow* win = nullptr);
    void toggle();
    MainWindow* win;
private slots:
    void updateTheme(int index);
private:
    QComboBox* styleBox;
};

#endif // PREFWINDOW_H
