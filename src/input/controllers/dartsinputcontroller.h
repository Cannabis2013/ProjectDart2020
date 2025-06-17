#ifndef DARTSINPUTCONTROLLER_H
#define DARTSINPUTCONTROLLER_H

#include "idartsinputcontroller.h"
#include <QObject>
#include <src/input/models/inputCandidate.h>

class ServiceCollection;
class DartsInput;

class DartsInputController : public QObject, public IDartsInputController {
        Q_OBJECT
public:
        DartsInputController(ServiceCollection* services);

        Q_INVOKABLE void add(const QByteArray& inputsAsJson) override;
        Q_INVOKABLE QByteArray inputs(const QString &name) override;
private:
        typedef QList<InputCandidate> Candidates;
        Candidates fromJson(const QByteArray& json) const;
        // Services
        ServiceCollection* const _services;
};

#endif // DARTSINPUTCONTROLLER_H
