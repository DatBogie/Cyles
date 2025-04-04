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
    // std::cout << std::to_string(event->key()) << std::endl;
    if ((event->modifiers() & Qt::ControlModifier) && event->key() == Qt::Key_Up) {
        win->upOneDir();
        return;
    }
    if ((event->modifiers() & Qt::ControlModifier) && event->key() == Qt::Key_Left) {
        win->addrBack();
        return;
    }
    if ((event->modifiers() & Qt::ControlModifier) && event->key() == Qt::Key_Right) {
        win->addrForward();
        return;
    }
    if ((event->modifiers() & Qt::ControlModifier) && event->key() == Qt::Key_Return) {
        win->openFile(this->currentIndex());
        return;
    }

    if ((event->key() >= 32 && event->key() <= 96) || (event->key() >= 123 && event->key() <= 126)) {
        QString newFilter = win->fltrBar->text()+QString(static_cast<char>(event->key())).toLower();
        win->fltrBar->setText(newFilter);
        // win->updateFilter(newFilter);
        return;
    }
    if (event->key() == Qt::Key_Backspace) {
        QString newFilter = win->fltrBar->text().mid(0,win->fltrBar->text().size()-1).toLower();
        win->fltrBar->setText(newFilter);
        return;
    }

    switch (event->key()) {
    case Qt::Key_Delete:
        win->delFile(this->currentIndex());
        break;
    case Qt::Key_Return:
        win->renameFile(this->currentIndex());
        break;
    case Qt::Key_Left:
    case Qt::Key_Right:
    case Qt::Key_Up:
    case Qt::Key_Down:
        QTreeView::keyPressEvent(event);
        break;
    }
}
