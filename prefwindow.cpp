#include "prefwindow.h"
#include "mainwindow.h"
#include "cylesutils.h"
#include "cylessignals.h"
#include "themebuilder.h"
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QPushButton>
#include <QComboBox>
#include <QStyleFactory>
#include <QLabel>
#include <QSizePolicy>
#include <iostream>
#include <QTimer>
#include <QInputDialog>
#include <QList>

PrefWindow::PrefWindow(MainWindow* win) {
    setFixedSize(400,300);

    this->win = win;

    setWindowFlag(Qt::WindowType::WindowStaysOnTopHint, true);
    setWindowFlag(Qt::WindowType::WindowMinimizeButtonHint, false);

    QVBoxLayout* mainLay = new QVBoxLayout();
    setLayout(mainLay);

    mainLay->setAlignment(Qt::AlignmentFlag::AlignTop);

    QHBoxLayout* styleLay = new QHBoxLayout();
    mainLay->addLayout(styleLay);

    QLabel* styleLbl = new QLabel("Widget Style:  ");
    styleLay->addWidget(styleLbl);

    styleBox = new QComboBox();
    styleBox->addItem("Default");
    styleBox->addItem("System");
    styleBox->addItems(QStyleFactory::keys());
    styleBox->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Preferred);
    styleLay->addWidget(styleBox);
    connect(styleBox,&QComboBox::activated,this,&PrefWindow::updateStyle);

    QHBoxLayout* themeLay = new QHBoxLayout();
    mainLay->addLayout(themeLay);

    QLabel* themeLbl = new QLabel("Theme: ");
    themeLay->addWidget(themeLbl);

    themeBox = new QComboBox();
    themeBox->addItem("System");
    themeBox->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Preferred);
    themeLay->addWidget(themeBox);
    connect(themeBox,&QComboBox::activated,this,&PrefWindow::updateTheme);

    QHBoxLayout* themeBtns = new QHBoxLayout();
    mainLay->addLayout(themeBtns);

    QPushButton* newTheme = new QPushButton("New Theme...");
    themeBtns->addWidget(newTheme);
    connect(newTheme,&QPushButton::clicked,this,&PrefWindow::createTheme);
    QPushButton* delTheme = new QPushButton("Delete Theme...");
    themeBtns->addWidget(delTheme);
    connect(delTheme,&QPushButton::clicked,this,&PrefWindow::deleteTheme);

    connect(CylesUtils::Signals,&CylesSignals::ThemesUpdated,this,&PrefWindow::themesUpdated);
}

void PrefWindow::toggle() {
    setVisible(!isVisible());
}

void PrefWindow::updateStyle(int index) {
    QString styleName = styleBox->itemText(index);
    if (styleName == "System")
        win->app->setStyle(QStyleFactory::create(CylesUtils::SystemStyle));
    else if (styleName == "Default")
        win->app->setStyle(QStyleFactory::create(CylesUtils::DefaultStyle));
    else
        win->app->setStyle(QStyleFactory::create(styleName));
}

void PrefWindow::updateTheme(int index) {
    QString themeName = themeBox->itemText(index);
    CylesUtils::CurrentTheme = themeName;
    CylesUtils::ApplyTheme(win->app);
    // CylesUtils::ApplyTheme(this);
}

void PrefWindow::createTheme() {
    ThemeBuilder* newTheme = new ThemeBuilder();
    connect(newTheme,&ThemeBuilder::completed,this,[](const Theme theme) {
        CylesUtils::Themes[theme.Name] = theme;
    });
}

void PrefWindow::deleteTheme() {
    QList<QString> keys = CylesUtils::Themes.keys();
    if (keys.size() < CylesUtils::ProtectedThemes.size()) return;
    QList<QString> themes;
    for (const QString &key : std::as_const(keys))
        if (!CylesUtils::ProtectedThemes.contains(key))
            themes.append(key);
    bool s;
    QString themeName = QInputDialog::getItem(this,"Delete Theme","Choose a theme to delete:",themes,0,false,&s);
    if (!s) return;
    if (CylesUtils::Themes.contains(themeName)) {
        CylesUtils::Themes.remove(themeName);
        emit CylesUtils::Signals->ThemesUpdated();
    }
}

void PrefWindow::themesUpdated() {
    themeBox->clear();
    themeBox->addItem("System");
    themeBox->addItems(CylesUtils::Themes.keys());
}
