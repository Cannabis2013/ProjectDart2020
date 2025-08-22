#ifndef ISCORESCONTROLLER_H
#define ISCORESCONTROLLER_H

class QByteArray;
class QString;

class IScoresController {
public:
    virtual int current() const = 0;
    virtual QString finishRow() const = 0;
};

#endif // ISCORESCONTROLLER_H
