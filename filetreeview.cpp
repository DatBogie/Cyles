#include "filetreeview.h"
#include "mainwindow.h"
#include <QTreeView>
#include <QWidget>
#include <iostream>

FileTreeView::FileTreeView(MainWindow* win)
    : QTreeView{}
{
    this->win = win;
}

void FileTreeView::keyPressEvent(QKeyEvent *event) {
    if ((event->modifiers() & Qt::ControlModifier) && event->key() == Qt::Key_Up) {
        win->upOneDir();
        return;
    }

    switch (event->key()) {
    case Qt::Key_Delete:
        win->delFile(this->currentIndex());
        break;
    case Qt::Key_Return:
        win->renameFile(this->currentIndex());
        break;
    case Qt::Key_Space:
        win->openFile(this->currentIndex());
    default:
        QTreeView::keyPressEvent(event);
        break;
    }
}
