#ifndef DARTSOPENINGFILTER_H
#define DARTSOPENINGFILTER_H

#include "iopeningfilter.h"

#include <QHash>

class InputsValidationPersistence;
class ServiceCollection;
class DartsOpeningFilter : public IOpeningFilter
{
public:
    DartsOpeningFilter(ServiceCollection* services);

    void saveState() override;
    void initFromFile() override;
    void init(const QList<QString> &names, bool withOpening, const QString& openingMod) override;
    void reset() override;
    QList<InputCandidate> filter(const QList<InputCandidate> &inputs) override;
    void update(const QString &name, bool allowed) override;
    bool isValid(const int& point, const QString& mod) const override;

private:
    QHash<QString, bool> _allowances;
    ServiceCollection* _services;
    QString _openingModifier = "D";
    InputsValidationPersistence *_persistence;
};

#endif // DARTSOPENINGFILTER_H
