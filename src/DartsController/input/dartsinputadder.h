#ifndef DARTSINPUTADDER_H
#define DARTSINPUTADDER_H

#include "idartsinputadder.h"

#include <QObject>

class ServiceCollection;
class Input;

class DartsInputAdder : public QObject, public IDartsInputAdder {
        Q_OBJECT
public:
        DartsInputAdder(ServiceCollection* services);

        Q_INVOKABLE void add(const QString& mod, const int& point) override;

private:
        // Private member methods
        void evaluateAndPersist(const Input& input);

        // Services
        ServiceCollection* const _services;
};

#endif // DARTSINPUTADDER_H
