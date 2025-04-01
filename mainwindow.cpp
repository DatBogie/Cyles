#include "mainwindow.h"
#include "FileFilterProxyModel.h"
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
#include <QDesktopServices>
#include <QString>
#include <QUrl>
#include <QIcon>
#include <QSortFilterProxyModel>

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

    QPushButton* upDir = new QPushButton(QIcon::fromTheme(QIcon::ThemeIcon::GoUp),"");
    topBar->addWidget(upDir);
    connect(upDir,&QPushButton::clicked,this,&MainWindow::upOneDir);

    addrBar = new QLineEdit(QDir::homePath());
    topBar->addWidget(addrBar);
    connect(addrBar,&QLineEdit::returnPressed,this,&MainWindow::updateAddress);

    fileModel = new QFileSystemModel();

    fileTree = new QTreeView();
    mainLay->addWidget(fileTree);
    connect(fileTree,&QTreeView::doubleClicked,this,&MainWindow::openFile);

    fileProxy = new FileFilterProxyModel();
    fileProxy->setSourceModel(fileModel);
    fileProxy->setFilterCaseSensitivity(Qt::CaseInsensitive);

    QHBoxLayout* btmBar = new QHBoxLayout();
    mainLay->addLayout(btmBar);

    fltrBar = new QLineEdit();
    btmBar->addWidget(fltrBar);
    connect(fltrBar,&QLineEdit::textChanged,this,&MainWindow::updateFilter);

    fileProxy->setSourceModel(fileModel);
    fileTree->setModel(fileProxy);

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
    fileTree->setRootIndex(fileProxy->mapFromSource(fileModel->index(address)));
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

void MainWindow::upOneDir() {
    QModelIndex currRoot = fileTree->rootIndex();
    QModelIndex parInd = currRoot.parent();
    if (parInd.isValid()) {
        addrBar->setText(fileModel->filePath(parInd));
        updateAddress();
    }
}

void MainWindow::updateFilter(const QString &fltr) {
    fileProxy->setFilterRegularExpression(QRegularExpression(fltr, QRegularExpression::CaseInsensitiveOption));
    fileTree->setRootIndex(fileProxy->mapFromSource(fileModel->index(address)));
}
