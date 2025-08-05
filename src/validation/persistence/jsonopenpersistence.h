#ifndef JSONOPENPERSISTENCE_H
#define JSONOPENPERSISTENCE_H

#include <QHash>
#include "src/validation/persistence/ivalidationopenpersistence.h"

class JsonOpenPersistence : public IValidationOpenPersistence
{
public:
    QHash<QString, bool> readAllowances() const override;
    QString readModifier() const override;
    bool readEnabled() const override;
    void save(const QHash<QString,bool>& allowances, const QString& openModifier) override;

private:
    const QString _file = "openValidation.dat";
};

#endif // JSONOPENPERSISTENCE_H
