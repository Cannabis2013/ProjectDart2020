#ifndef IOPENVALIDATOR_H
#define IOPENVALIDATOR_H

#include <QString>
#include "src/input/inputCandidate.h"

class IOpenValidator
{
  public:
    virtual void saveState() = 0;
    virtual void reset() = 0;
    virtual void init(bool withOpening,const QString& openingMod = "D") = 0;
    virtual void initFromFile() = 0;
    virtual void update(const QString& name, bool allowed) = 0;
    virtual QList<InputCandidate> filter(const QList<InputCandidate>& inputs) = 0;
    virtual bool isValid(const int& point, const QString& mod) const = 0;
};

#endif // IOPENVALIDATOR_H
