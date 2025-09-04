#ifndef IREMAININGS_H
#define IREMAININGS_H

#include <QList>

class QByteArray;
class QString;

class IRemainings {
public:
    virtual QList<int> all() const = 0;
    virtual int remaining(const QString& playerName) const = 0;
    virtual int current() const = 0;
    virtual QString finishRow() const = 0;
};

#endif // IREMAININGS_H
