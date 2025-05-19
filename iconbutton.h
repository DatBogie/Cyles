#ifndef ICONBUTTON_H
#define ICONBUTTON_H

#include <QPushButton>
#include <QString>

class IconButton : public QPushButton
{
    Q_OBJECT
public:
    explicit IconButton();
    void setIcon(QString iconPath);
private slots:
    void iconColorChanged();
private:
    QString iconPath;
    void updateIcon();
};

#endif // ICONBUTTON_H
