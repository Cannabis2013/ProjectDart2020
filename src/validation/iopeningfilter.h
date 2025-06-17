#ifndef IOPENINGFILTER_H
#define IOPENINGFILTER_H

#include <QString>

#include <src/input/models/inputCandidate.h>

class IOpeningFilter{
public:
    virtual void saveState() = 0;
    virtual void reset() = 0;
    virtual void init(const QList<QString>& names, bool allowed,const QString& openingMod = "D") = 0;
    virtual void initFromFile() = 0;
    virtual void update(const QString& name, bool allowed) = 0;
    virtual bool allowed(const QString& name) const = 0;
    virtual QList<InputCandidate> filter(const QList<InputCandidate>& inputs) = 0;
};

#endif // IOPENINGFILTER_H
