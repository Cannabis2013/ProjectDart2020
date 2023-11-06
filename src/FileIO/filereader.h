#ifndef FILEREADER_H
#define FILEREADER_H

#include <QObject>

class FileReader : public QObject
{
        Q_OBJECT
public:
        Q_INVOKABLE QString readAsString(const QString& filepath);
};

#endif // FILEREADER_H
