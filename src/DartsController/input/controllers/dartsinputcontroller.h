#ifndef DARTSINPUTCONTROLLER_H
#define DARTSINPUTCONTROLLER_H

#include "idartsinputcontroller.h"

#include <QObject>

class ServiceCollection;
class Input;

class DartsInputController : public QObject, public IDartsInputController {
        Q_OBJECT
public:
        DartsInputController(ServiceCollection* services);

        Q_INVOKABLE void add(const QString& mod, const int& point) override;

private:
        // Services
        ServiceCollection* const _services;
};

#endif // DARTSINPUTCONTROLLER_H
