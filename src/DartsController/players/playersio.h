#ifndef PLAYERSIO_H
#define PLAYERSIO_H

#include <QStringList>

class PlayersIO
{
public:
        PlayersIO(const QString &filePath);

        QStringList initFromFile();
        bool saveToFile(const QStringList &names);

private:
        QString _filePath;
};

#endif // PLAYERSIO_H
