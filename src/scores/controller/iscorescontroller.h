#ifndef ISCORESCONTROLLER_H
#define ISCORESCONTROLLER_H

class QByteArray;
class QString;

class IScoresController {
public:
    virtual int currentRemaining() const = 0;
    virtual int current() const = 0;
    virtual QByteArray all() const = 0;
    virtual QString finishRow() const = 0;
    virtual int delta() const = 0;
};

#endif // ISCORESCONTROLLER_H
