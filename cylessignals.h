#ifndef CYLESSIGNALS_H
#define CYLESSIGNALS_H

#include <QObject>

class CylesSignals : public QObject
{
    Q_OBJECT
public:
    explicit CylesSignals(QObject *parent = nullptr);
signals:
//     void ThemesUpdated();
    void IconColorChanged();
};

#endif // CYLESSIGNALS_H
