#include "cylesutils.h"
#include <string>
#include <vector>
#include <QString>


const std::string CylesUtils::QStringVectorToStdString(std::vector<QString> x) {
    QString str = "[";
    int i = 0;
    for (const QString& v : x ) {
        if (!v.isEmpty() && i > 0) {
            str+=", ";
        }
        str+="\""+v+"\"";
        i++;
    }
    str+="]";
    return str.toStdString();
}
