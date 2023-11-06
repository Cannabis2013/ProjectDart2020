#include "filereader.h"

#include <QFile>
#include <QTextStream>

QString FileReader::readAsString(const QString& filepath)
{
        QFile file(filepath);
        if (!file.open(QIODevice::ReadOnly))
                return QString();
        QTextStream in(&file);
        return in.readAll();
}
