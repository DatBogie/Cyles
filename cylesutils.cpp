#include "cylesutils.h"
#include <string>
#include <vector>
#include <QString>
#include <QColor>
// #include "theme.h"
#include <QMap>
#include "cylessignals.h"
#include <QWidget>
#include <QApplication>
#include <QStyle>
#include <QStyleFactory>
#include <QPixmap>
#include <QMimeData>
#include <QUrl>
#include <QClipboard>
#include <QGuiApplication>
#include <QMessageBox>
#include <QFile>
#include <QFileInfo>
#include <QStandardPaths>
#include <QDebug>

CylesSignals* CylesUtils::Signals = new CylesSignals();

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

const QString CylesUtils::QColorToQString(QColor clr) {
    return "rgb(" + QString::number(clr.red()) + ", " + QString::number(clr.green()) + ", " + QString::number(clr.blue()) + ")";
}

const bool CylesUtils::IsQColorDark(QColor clr) {
    return clr.lightness() < 128;
}

// const void CylesUtils::ApplyTheme(QWidget* widget, Theme theme) {
//     if (theme.Name != "System") {
//         widget->setStyleSheet(theme.toQString());
//     } else {
//         widget->setStyleSheet("");
//         widget->setPalette(widget->style()->standardPalette());
//     }
// }

// const void CylesUtils::ApplyTheme(QWidget* widget) {
//     CylesUtils::ApplyTheme(widget, CylesUtils::Themes[CylesUtils::CurrentTheme]);
// }

// const void CylesUtils::ApplyTheme(QApplication* app, Theme theme) {
//     if (theme.Name != "System") {
//         app->setStyle(theme.toThemeStyle());
//     } else {
//         app->setStyle(QStyleFactory::create(DefaultStyle));
//         app->setPalette(app->style()->standardPalette());
//     }
// }

// const void CylesUtils::ApplyTheme(QApplication* app) {
//     CylesUtils::ApplyTheme(app, CylesUtils::Themes[CylesUtils::CurrentTheme]);
// }

#if defined(_WIN32)
const std::string CylesUtils::OS = "WIN";
#elif defined(__APPLE__)
const std::string CylesUtils::OS = "MAC";
#elif defined(__LINUX__)
const std::string CylesUtils::OS = "LIN";
#else
const std::string CylesUtils::OS = "OTHER";
#endif

// QColor CylesUtils::ButtonColor = Qt::white;
// QColor CylesUtils::TextInputColor = Qt::white;
// QColor CylesUtils::BackgroundColor = Qt::white;
// QColor CylesUtils::AccentColor = Qt::white;

QString CylesUtils::SystemStyle = "";
// QString CylesUtils::DefaultStyle = "Fusion";
// std::vector<QColor*> CylesUtils::colors = {&CylesUtils::ButtonColor,&CylesUtils::TextInputColor,&CylesUtils::BackgroundColor,&CylesUtils::AccentColor};

// QMap<QString, Theme> CylesUtils::Themes = {
//     std::pair{"Dark", Theme("Dark",true,std::vector<QColor>{QColor(45,45,45),QColor(35,35,35),QColor(25,25,25),QColor(21,106,175)})},
//     std::pair{"Light", Theme("Light",true,std::vector<QColor>{QColor(210,210,210),QColor(220,220,220),QColor(230,230,230),QColor(81,166,235)})}
// };
// QList<QString> CylesUtils::ProtectedThemes = {"System","Dark","Light"};
// QString CylesUtils::CurrentTheme = CylesUtils::Themes.firstKey();

bool CylesUtils::useDarkIcons = false;

void CylesUtils::copyFile(const QString &path) {
    QMimeData* mime = new QMimeData;
    QList<QUrl> urls;
    urls << QUrl::fromLocalFile(path);
    mime->setUrls(urls);

    QClipboard* clip = QGuiApplication::clipboard();
    clip->setMimeData(mime);
}

void CylesUtils::pasteFile(const QString &path, const QString &dest) {
    const QClipboard *clipboard = QGuiApplication::clipboard();
    const QMimeData *mimeData = clipboard->mimeData();

    if (mimeData->hasUrls()) {
        QList<QUrl> urls = mimeData->urls();

        for (const QUrl &url : urls) {
            if (!url.isLocalFile())
                continue;

            QString sourceFilePath = url.toLocalFile();
            QFileInfo fileInfo(sourceFilePath);
            QString destinationFilePath = dest + "/" + fileInfo.fileName();

            if (!QFile::copy(sourceFilePath, destinationFilePath)) {
                QMessageBox::critical(nullptr,"PyCuts","Failed to paste file.",QMessageBox::StandardButton::Ok,QMessageBox::StandardButton::Ok);
            }
        }
    }
}

QString CylesUtils::absPath(const QString &path) {
    QString result = path;
    if (path.startsWith("~")) {
        result = QStandardPaths::writableLocation(QStandardPaths::HomeLocation) + path.mid(1);
    }
    return result;
}
