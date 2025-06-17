#ifndef IDARTSINPUTCONTROLLER_H
#define IDARTSINPUTCONTROLLER_H

#include <qstring.h>

class IDartsInputController {
public:
    virtual void add(const QByteArray& inputs) = 0;
    virtual QByteArray inputs(const QString& name) = 0;
    virtual bool isValid(const int &point, const QString& mod) const = 0;
};

#endif // IDARTSINPUTCONTROLLER_H
