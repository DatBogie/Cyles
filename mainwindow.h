#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "FileFilterProxyModel.h"
#include <QMainWindow>
#include <QLineEdit>
#include <QString>
#include <QTreeView>
#include <QFileSystemModel>

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
private:
    QString address;
    QLineEdit* addrBar;
    QTreeView* fileTree;
    QFileSystemModel* fileModel;
    QLineEdit* fltrBar;
    FileFilterProxyModel* fileProxy;
private slots:
    void exit();
    void updateAddress();
    void openFile(const QModelIndex &index);
    void upOneDir();
    void updateFilter(const QString &fltr);
};
#endif // MAINWINDOW_H
