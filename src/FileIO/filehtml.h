#ifndef FILEREADER_H
#define FILEREADER_H

#include <QObject>

class FileHtml : public QObject {
        Q_OBJECT
public:
        Q_INVOKABLE QString aboutHtml();
};

#endif // FILEREADER_H
