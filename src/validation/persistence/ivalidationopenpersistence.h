#ifndef IVALIDATIONOPENPERSISTENCE_H
#define IVALIDATIONOPENPERSISTENCE_H

#include <QString>

class IValidationOpenPersistence{
public:
    virtual QHash<QString, bool> readAllowances() const = 0;
    virtual QString readModifier() const = 0;
    virtual bool readEnabled() const = 0;
    virtual void save(const QHash<QString,bool>& allowances, const QString& openModifier) = 0;
};

#endif // IVALIDATIONOPENPERSISTENCE_H
