#ifndef MAINWINDOW_H
#define MAINWINDOW_H

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
private slots:
    void exit();
    void updateAddress();
};
#endif // MAINWINDOW_H
