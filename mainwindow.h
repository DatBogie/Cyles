#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QLineEdit>
#include <QString>
#include <QTreeView>
#include <QFileSystemModel>
#include <QMenu>

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
    QMenu* fileContext;
private slots:
    void exit();
    void updateAddress();
    void openFile(const QModelIndex &index);
    void upOneDir();
    void updateFilter(const QString &fltr);
    void fileContextMenu(const QPoint &pt);
};
#endif // MAINWINDOW_H
