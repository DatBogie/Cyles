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

#if defined(_WIN32)
const std::string CylesUtils::OS = "WIN";
#elif defined(__APPLE__)
const std::string CylesUtils::OS = "MAC";
#elif defined(__LINUX__)
const std::string CylesUtils::OS = "LIN";
#else
const std::string CylesUtils::OS = "OTHER";
#endif

QString CylesUtils::SystemStyle = "";
