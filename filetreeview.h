#ifndef FILETREEVIEW_H
#define FILETREEVIEW_H

#include "mainwindow.h"
#include <QTreeView>
#include <QWidget>
#include <QKeyEvent>

#pragma once
class MainWindow;

class FileTreeView : public QTreeView
{
    Q_OBJECT
public:
    explicit FileTreeView(MainWindow* win);
    MainWindow* win;
protected:
    void keyPressEvent(QKeyEvent *event) override;
};

#endif // FILETREEVIEW_H
