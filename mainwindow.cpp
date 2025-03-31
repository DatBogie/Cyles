#include "mainwindow.h"
#include <QMenuBar>
#include <QMenu>
#include <QAction>
#include <QWidget>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QLabel>
#include <QPushButton>
#include <QLineEdit>
#include <QSizePolicy>
#include <QDir>
#include <QTreeView>
#include <QFileSystemModel>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    setMinimumSize(640,480);
    QMenuBar* menu = menuBar();
    QMenu* fileM = menu->addMenu(tr("&File"));
    QAction* exitAct = fileM->addAction(tr("E&xit"));
    connect(exitAct,&QAction::triggered,this,&MainWindow::exit);

    QWidget* win = new QWidget();
    setCentralWidget(win);
    QVBoxLayout* mainLay = new QVBoxLayout(win);
    mainLay->setAlignment(Qt::AlignmentFlag::AlignTop);

    QHBoxLayout* topBar = new QHBoxLayout();
    mainLay->addLayout(topBar);

    addrBar = new QLineEdit(QDir::homePath());
    mainLay->addWidget(addrBar);
    connect(addrBar,&QLineEdit::returnPressed,this,&MainWindow::updateAddress);

    fileModel = new QFileSystemModel();
    fileTree = new QTreeView();

    mainLay->addWidget(fileTree);

    updateAddress();
}

MainWindow::~MainWindow() {}

void MainWindow::exit() {
    close();
}

void MainWindow::updateAddress() {
    address = addrBar->text();
    fileModel->setRootPath(address);
    fileTree->setModel(fileModel);
    fileTree->setRootIndex(fileModel->index(address));
}
