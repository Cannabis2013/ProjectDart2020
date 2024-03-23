#include "filehtml.h"

#include <QFile>
#include <QTextStream>

QString FileHtml::aboutHtml()
{
        QFile file(":/data/Ressources/TextData/aboutContent.dat");
        if (!file.open(QIODevice::ReadOnly))
                return QString();
        QTextStream in(&file);
        return in.readAll();
}
