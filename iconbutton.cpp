#include "iconbutton.h"
#include "cylesutils.h"
#include "cylessignals.h"
#include <QPushButton>
#include <QIcon>
#include <iostream>

IconButton::IconButton() : QPushButton{} {
    connect(CylesUtils::Signals,&CylesSignals::IconColorChanged,this,&IconButton::iconColorChanged);
}

void IconButton::setIcon(QString iconPath) {
    this->iconPath = iconPath;
    updateIcon();
}

void IconButton::iconColorChanged() {
    if (iconPath.contains("_black"))
        iconPath = iconPath.replace("_black","_white");
    else
        iconPath = iconPath.replace("_white","_black");
    updateIcon();
}

void IconButton::updateIcon() {
    QPushButton::setIcon(QIcon(iconPath));
}
