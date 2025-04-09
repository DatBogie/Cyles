#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "filetreeview.h"
#include <QMainWindow>
#include <QLineEdit>
#include <QString>
#include <QFileSystemModel>
#include <QMenu>
#include <vector>
#include <QApplication>

#pragma once
class FileTreeView;

#include "theme.h"
#pragma once
class Theme;

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    QLineEdit* fltrBar;
    QApplication* app;
private:
    QString address;
    std::vector<QString> addrHistory;
    QLineEdit* addrBar;
    FileTreeView* fileTree;
    QFileSystemModel* fileModel;
    QMenu* fileContext;
    int addrInd = 0;
public slots:
    void mkDir();
    void mkDirFromPath(QString filePath);
    void touch();
    void touchFromPath(QString filePath);
    void exit();
    void updateAddress();
    void updateAddressNoHistory();
    void openFile(const QModelIndex &index);
    void renameFile(const QModelIndex &index);
    void delFile(const QModelIndex &index);
    void upOneDir();
    void addrBack();
    void addrForward();
    void updateFilter(const QString &fltr);
    void fileContextMenu(const QPoint &pt);
protected:
    void keyPressEvent(QKeyEvent *event) override;
};
#endif // MAINWINDOW_H
