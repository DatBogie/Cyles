#include <QSortFilterProxyModel>
#include "FileFilterProxyModel.h"

bool FileFilterProxyModel::filterAcceptsRow(int sourceRow, const QModelIndex &sourceParent) const {
    if (!sourceModel()) return false;

    QModelIndex index = sourceModel()->index(sourceRow, 0, sourceParent);
    QString fileName = sourceModel()->data(index, Qt::DisplayRole).toString();

    // Skip root directories (e.g., /, home, dat-bogie, etc.)
    // Check if the sourceParent is the root directory (not valid for filtering)
    if (sourceParent == QModelIndex()) {
        return false; // If sourceParent is invalid (root), do not filter root-level directories
    }

    // If the fileName is empty (or something like `.` or `..`), we skip it
    if (fileName.isEmpty() || fileName == "." || fileName == "..") {
        return false;
    }

    // Perform the regular expression filter on the file name
    QRegularExpression regExp = filterRegularExpression();
    QRegularExpressionMatch match = regExp.match(fileName);

    std::cout << fileName.toStdString() << std::endl;
    std::cout << std::to_string(match.hasMatch()) << std::endl;

    return match.hasMatch(); // Return true if the name matches the filter
}
