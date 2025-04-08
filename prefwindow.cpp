#include "prefwindow.h"
#include "mainwindow.h"
#include "cylesutils.h"
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QPushButton>
#include <QComboBox>
#include <QStyleFactory>
#include <QLabel>
#include <QSizePolicy>

PrefWindow::PrefWindow(MainWindow* win) {
    setFixedSize(400,300);

    this->win = win;

    setWindowFlag(Qt::WindowType::WindowStaysOnTopHint, true);
    setWindowFlag(Qt::WindowType::WindowMinimizeButtonHint, false);

    QVBoxLayout* mainLay = new QVBoxLayout();
    setLayout(mainLay);

    mainLay->setAlignment(Qt::AlignmentFlag::AlignTop);

    QHBoxLayout* styleLay = new QHBoxLayout();

    QLabel* styleLbl = new QLabel("Widget Style:  ");
    styleLay->addWidget(styleLbl);

    styleBox = new QComboBox();
    styleBox->addItem("System");
    styleBox->addItems(QStyleFactory::keys());
    styleBox->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Preferred);
    styleLay->addWidget(styleBox);
    connect(styleBox,&QComboBox::activated,this,&PrefWindow::updateTheme);

    mainLay->addLayout(styleLay);
}

void PrefWindow::toggle() {
    setVisible(!isVisible());
}

void PrefWindow::updateTheme(int index) {
    QString styleName = styleBox->itemText(index);
    if (styleName != "System")
        win->app->setStyle(QStyleFactory::create(styleName));
    else
        win->app->setStyle(QStyleFactory::create(CylesUtils::SystemStyle));
}
