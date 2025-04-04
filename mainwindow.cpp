#include "mainwindow.h"
#include "filetreeview.h"
#include "cylesutils.h"
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
#include <QFileSystemModel>
#include <QDesktopServices>
#include <QString>
#include <QUrl>
#include <QIcon>
#include <QSortFilterProxyModel>
#include <QIcon>
#include <QInputDialog>
#include <QMessageBox>
#include <iostream>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    setWindowTitle("Cyles");
    setMinimumSize(640,480);
    QMenuBar* menu = menuBar();
    QMenu* fileM = menu->addMenu(tr("&File"));
    connect(fileM->addAction(tr("New &Folder")),&QAction::triggered,this,&MainWindow::mkDir);
    connect(fileM->addAction(tr("&New File")),&QAction::triggered,this,&MainWindow::touch);
    QAction* exitAct = fileM->addAction(tr("E&xit"));
    exitAct->setMenuRole(QAction::NoRole);
    connect(exitAct,&QAction::triggered,this,&MainWindow::exit);

    QWidget* win = new QWidget();
    setCentralWidget(win);
    QVBoxLayout* mainLay = new QVBoxLayout(win);
    mainLay->setAlignment(Qt::AlignmentFlag::AlignTop);

    QHBoxLayout* topBar = new QHBoxLayout();
    mainLay->addLayout(topBar);

    QPushButton* addrBack = new QPushButton(QIcon(":/images/arrow_back_white.svg"),"");
    topBar->addWidget(addrBack);
    connect(addrBack,&QPushButton::clicked,this,&MainWindow::addrBack);
    if (CylesUtils::OS != "MAC")
        addrBack->setToolTip("Ctrl + Left");
    else
        addrBack->setToolTip("CMD + Left");

    QPushButton* addrFwd = new QPushButton(QIcon(":/images/arrow_forward_white.svg"),"");
    topBar->addWidget(addrFwd);
    connect(addrFwd,&QPushButton::clicked,this,&MainWindow::addrForward);
    if (CylesUtils::OS != "MAC")
        addrFwd->setToolTip("Ctrl + Right");
    else
        addrFwd->setToolTip("CMD + Right");

    QPushButton* upDir = new QPushButton(QIcon(":/images/arrow_up_white.svg"),"");
    topBar->addWidget(upDir);
    connect(upDir,&QPushButton::clicked,this,&MainWindow::upOneDir);
    if (CylesUtils::OS != "MAC")
        upDir->setToolTip("Ctrl + Up");
    else
        upDir->setToolTip("CMD + Up");

    QHBoxLayout* midBar = new QHBoxLayout();
    mainLay->addLayout(midBar);

    address = QDir::homePath();
    addrHistory.push_back(address);

    addrBar = new QLineEdit(address);
    topBar->addWidget(addrBar);
    connect(addrBar,&QLineEdit::returnPressed,this,&MainWindow::updateAddress);

    fileModel = new QFileSystemModel();

    fileTree = new FileTreeView(this);
    mainLay->addWidget(fileTree);
    connect(fileTree,&FileTreeView::doubleClicked,this,&MainWindow::openFile);

    fileTree->setContextMenuPolicy(Qt::ContextMenuPolicy::CustomContextMenu);
    connect(fileTree, &FileTreeView::customContextMenuRequested, this, &MainWindow::fileContextMenu);

    QHBoxLayout* btmBar = new QHBoxLayout();
    mainLay->addLayout(btmBar);

    fltrBar = new QLineEdit();
    fltrBar->setPlaceholderText("Type to filter...");
    btmBar->addWidget(fltrBar);
    connect(fltrBar,&QLineEdit::textChanged,this,&MainWindow::updateFilter);

    fileTree->setModel(fileModel);

    fileContext = new QMenu();

    updateAddressNoHistory();
}

MainWindow::~MainWindow() {}

void MainWindow::exit() {
    close();
}

void MainWindow::updateAddress() {
    address = addrBar->text();
    fileModel->setRootPath(address);
    fileTree->setRootIndex(fileModel->index(address));
    addrInd++;
    if (addrInd > addrHistory.size()) addrHistory.resize(addrHistory.size()+1);
    addrHistory.insert(addrHistory.begin() + addrInd, address);
    std::cout << CylesUtils::QStringVectorToStdString(addrHistory) << std::endl << std::to_string(addrInd) << std::endl;
    updateFilter("");
}

void MainWindow::updateAddressNoHistory() {
    address = addrBar->text();
    fileModel->setRootPath(address);
    fileTree->setRootIndex(fileModel->index(address));
    std::cout << CylesUtils::QStringVectorToStdString(addrHistory) << std::endl << std::to_string(addrInd) << std::endl;
    updateFilter("");
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
    QString name = QInputDialog::getText(this,"Rename File","Rename '"+QFileInfo(filePath).fileName()+"' to:",QLineEdit::Normal,"",&s);
    if (!s) return;
    QFile f(filePath);
    f.rename(QFileInfo(filePath).dir().path()+"/"+name);
    updateAddress();
}

void MainWindow::delFile(const QModelIndex &index) {
    QString filePath = fileModel->filePath(index);
    QMessageBox::StandardButton s = QMessageBox::warning(this,"Delete File","Delete "+QFileInfo(filePath).fileName()+" perminently?",QMessageBox::StandardButton::Yes | QMessageBox::StandardButton::Cancel,QMessageBox::StandardButton::Cancel);
    if (s == QMessageBox::StandardButton::Cancel) return;
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

void MainWindow::addrBack() {
    if (addrInd-1 < 0) return;
    addrInd--;
    addrBar->setText(addrHistory[addrInd]);
    updateAddressNoHistory();
}

void MainWindow::addrForward() {
    if (addrInd+1 >= addrHistory.size()) return;
    addrInd++;
    addrBar->setText(addrHistory[addrInd]);
    updateAddressNoHistory();
}

void MainWindow::updateFilter(const QString &fltr) {
    QModelIndex root = fileModel->index(fileModel->rootPath());
    int firstInd = fileModel->rowCount(root);
    for (int y=0; y<fileModel->rowCount(root); ++y) {
        QModelIndex ind = fileModel->index(y,0,root);
        if (!ind.isValid()) continue;
        QString filePath = fileModel->filePath(ind);
        bool hide = !(QFileInfo(filePath).fileName().toLower().contains(fltr.toLower()));
        fileTree->setRowHidden(y,root,hide);
        if (!hide && y< firstInd) firstInd=y;
    }
    if (firstInd < fileModel->rowCount(root)) {
        fileTree->setCurrentIndex(fileModel->index(firstInd,0,root));
    }
}

void MainWindow::fileContextMenu(const QPoint &pt) {
    QModelIndex ind = fileTree->indexAt(pt);
    if (!ind.isValid()) return;
    QString filePath = fileModel->filePath(ind);
    fileContext->clear();
    connect(fileContext->addAction("Open"),&QAction::triggered,this,[this, ind](void){ openFile(ind); });
    connect(fileContext->addAction("Rename"),&QAction::triggered,this,[this, ind](void){ renameFile(ind); });
    connect(fileContext->addAction("Delete"),&QAction::triggered,this,[this, ind](void){ delFile(ind); });
    if (QFileInfo(filePath).isDir()) {
        fileContext->addSeparator();
        connect(fileContext->addAction("New Folder Here"),&QAction::triggered,this,[this, filePath](void){ mkDirFromPath(filePath); });
        connect(fileContext->addAction("New File Here"),&QAction::triggered,this,[this, filePath](void){ touchFromPath(filePath); });
    } else {
        connect(fileContext->addAction("New Folder"),&QAction::triggered,this,[this, filePath](void){ mkDirFromPath(filePath); });
        connect(fileContext->addAction("New File"),&QAction::triggered,this,[this, filePath](void){ touchFromPath(filePath); });
    }
    fileContext->exec(fileTree->viewport()->mapToGlobal(pt));
}

void MainWindow::mkDir() {
    bool s;
    QString name = QInputDialog::getText(this,"Create Folder","Folder name:",QLineEdit::Normal,"",&s);
    if (!s) return;
    QDir(address).mkdir(name);
}

void MainWindow::mkDirFromPath(QString filePath) {
    bool s;
    QString name = QInputDialog::getText(this,"Create Folder","Folder name:",QLineEdit::Normal,"",&s);
    if (!s) return;
    QDir(filePath).mkdir(name);
}

void MainWindow::touch() {
    bool s;
    QString name = QInputDialog::getText(this,"Create File","File name:",QLineEdit::Normal,"",&s);
    if (!s) return;
    QFile f(QFileInfo(address).filePath()+"/"+name);
    if (f.open(QIODevice::WriteOnly)) {
        f.close();
    }
}

void MainWindow::touchFromPath(QString filePath) {
    bool s;
    QString name = QInputDialog::getText(this,"Create File","File name:",QLineEdit::Normal,"",&s);
    if (!s) return;
    QFile f(QFileInfo(filePath).filePath()+"/"+name);
    if (f.open(QIODevice::WriteOnly)) {
        f.close();
    }
}
