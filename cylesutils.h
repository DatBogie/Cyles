#ifndef CYLESUTILS_H
#define CYLESUTILS_H

#include <string>
#include <vector>
#include <QString>

class CylesUtils
{
public:
    static const std::string QStringVectorToStdString(std::vector<QString> x);
};

#endif // CYLESUTILS_H
