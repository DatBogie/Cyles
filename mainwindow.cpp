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
#include <QFile>
#include <QTreeView>
#include <QFileSystemModel>
#include <QDesktopServices>
#include <QString>
#include <QUrl>
#include <QIcon>
#include <QSortFilterProxyModel>
#include <QIcon>
#include <QInputDialog>
#include <iostream>

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



    QPushButton* upDir = new QPushButton(QIcon("../../../../../images/arrow_up_white.svg"),"");
    topBar->addWidget(upDir);
    connect(upDir,&QPushButton::clicked,this,&MainWindow::upOneDir);

    addrBar = new QLineEdit(QDir::homePath());
    topBar->addWidget(addrBar);
    connect(addrBar,&QLineEdit::returnPressed,this,&MainWindow::updateAddress);

    fileModel = new QFileSystemModel();

    fileTree = new QTreeView();
    mainLay->addWidget(fileTree);
    connect(fileTree,&QTreeView::doubleClicked,this,&MainWindow::openFile);

    fileTree->setContextMenuPolicy(Qt::ContextMenuPolicy::CustomContextMenu);
    connect(fileTree, &QTreeView::customContextMenuRequested, this, &MainWindow::fileContextMenu);

    QHBoxLayout* btmBar = new QHBoxLayout();
    mainLay->addLayout(btmBar);

    fltrBar = new QLineEdit();
    btmBar->addWidget(fltrBar);
    connect(fltrBar,&QLineEdit::textChanged,this,&MainWindow::updateFilter);

    fileTree->setModel(fileModel);

    fileContext = new QMenu();

    updateAddress();
}

MainWindow::~MainWindow() {}

void MainWindow::exit() {
    close();
}

void MainWindow::updateAddress() {
    address = addrBar->text();
    fileModel->setRootPath(address);
    // fileProxy->setSourceModel(fileModel);
    // fileTree->setModel(fileProxy);
    fileTree->setRootIndex(fileModel->index(address));
    // fileTree->setRootIndex(fileProxy->mapFromSource(fileModel->index(address)));
}

void MainWindow::openFile(const QModelIndex &index) {
    QString filePath = fileModel->filePath(index);
    if (QFileInfo(filePath).isFile()) {
        QDesktopServices::openUrl(QUrl::fromLocalFile(filePath));
    } else {
        addrBar->setText(filePath);
        updateAddress();
    }
}

void MainWindow::renameFile(const QModelIndex &index) {
    QString filePath = fileModel->filePath(index);
    bool s;
    QString name = QInputDialog::getText(this,"Rename File","Rename file to:",QLineEdit::Normal,"",&s);
    if (!s) return;
    QFile f(filePath);
    f.rename(QFileInfo(filePath).dir().path()+"/"+name);
    updateAddress();
}

void MainWindow::delFile(const QModelIndex &index) {
    QString filePath = fileModel->filePath(index);
    if (QFileInfo(filePath).isDir()) {
        QDir(filePath).removeRecursively();
    } else {
        QFile(filePath).remove();
    }
}

void MainWindow::upOneDir() {
    QModelIndex currRoot = fileTree->rootIndex();
    QModelIndex parInd = currRoot.parent();
    if (parInd.isValid()) {
        addrBar->setText(fileModel->filePath(parInd));
        updateAddress();
    }
}

void MainWindow::updateFilter(const QString &fltr) {
    QModelIndex root = fileModel->index(fileModel->rootPath());
    for (int y=0; y<fileModel->rowCount(root); ++y) {
        QModelIndex ind = fileModel->index(y,0,root);
        if (!ind.isValid()) continue;
        QString filePath = fileModel->filePath(ind);
        fileTree->setRowHidden(y,root, !(QFileInfo(filePath).fileName().toLower().contains(fltr.toLower())) );
    }
}

void MainWindow::fileContextMenu(const QPoint &pt) {
    QModelIndex ind = fileTree->indexAt(pt);
    if (!ind.isValid()) return;
    QString filePath = fileModel->filePath(ind);
    if (QFileInfo(filePath).isDir()) {

    } else {

    }
    fileContext->clear();
    connect(fileContext->addAction("Open"),&QAction::triggered,this,[this, ind](void){ openFile(ind); });
    connect(fileContext->addAction("Rename"),&QAction::triggered,this,[this, ind](void){ renameFile(ind); });
    connect(fileContext->addAction("Delete"),&QAction::triggered,this,[this, ind](void){ delFile(ind); });
    fileContext->exec(fileTree->viewport()->mapToGlobal(pt));
}
