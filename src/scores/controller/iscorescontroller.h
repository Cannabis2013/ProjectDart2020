#ifndef ISCORESCONTROLLER_H
#define ISCORESCONTROLLER_H

#include <QList>

class QByteArray;
class QString;

class IScoresController {
public:
    virtual QList<int> all() const = 0;
    virtual int current() const = 0;
    virtual QString finishRow() const = 0;
};

#endif // ISCORESCONTROLLER_H
