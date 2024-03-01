#ifndef FILEREADER_H
#define FILEREADER_H

#include <QObject>

class PageTexts : public QObject {
        Q_OBJECT
public:
        Q_INVOKABLE QString aboutPage();
};

#endif // FILEREADER_H
