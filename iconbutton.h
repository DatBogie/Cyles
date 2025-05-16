#ifndef ICONBUTTON_H
#define ICONBUTTON_H

#include <QPushButton>

class IconButton : public QPushButton
{
    Q_OBJECT
public:
    explicit IconButton(QObject *parent = nullptr);
signals:
    void iconColorChanged();
};

#endif // ICONBUTTON_H
