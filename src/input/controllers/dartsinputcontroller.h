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

        Q_INVOKABLE void add(const QByteArray& inputs) override;

private:
        typedef QList<InputCandidate> Candidates;
        Candidates filteredInputs(const Candidates& candidates) const;
        Candidates fromJson(const QByteArray& json) const;
        // Services
        ServiceCollection* const _services;
};

#endif // DARTSINPUTCONTROLLER_H
