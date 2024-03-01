#include "pagetexts.h"

#include <QFile>
#include <QTextStream>

#define AboutText ":/data/Ressources/TextData/aboutContent.dat"

QString PageTexts::aboutPage()
{
        QFile file(AboutText);
        if (!file.open(QIODevice::ReadOnly))
                return QString();
        QTextStream in(&file);
        return in.readAll();
}
