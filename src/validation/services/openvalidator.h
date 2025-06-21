#ifndef OPENVALIDATOR_H
#define OPENVALIDATOR_H

#include "iopenvalidator.h"

#include <QHash>

class JsonOpenPersistence;
class ServiceCollection;
class OpenValidator : public IOpenValidator
{
public:
    OpenValidator(ServiceCollection* services);

    void saveState() override;
    void initFromFile() override;
    void init(bool withOpening, const QString& openingMod) override;
    void reset() override;
    QList<InputCandidate> filter(const QList<InputCandidate> &inputs) override;
    void update(const QString &name, bool allowed) override;
    bool isValid(const int& point, const QString& mod) const override;

private:
    bool _withOpen = false;
    QHash<QString, bool> _allowances;
    ServiceCollection* _services;
    QString _openingModifier = "D";
};

#endif // OPENVALIDATOR_H
