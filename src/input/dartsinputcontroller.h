#ifndef DARTSINPUTCONTROLLER_H
#define DARTSINPUTCONTROLLER_H

#include <QObject>
#include "idartsinputcontroller.h"
#include "src/input/inputCandidate.h"

class ServiceCollection;
class DartsInput;

class DartsInputController : public QObject, public IDartsInputController {
        Q_OBJECT
public:
    DartsInputController(ServiceCollection* services);

    Q_INVOKABLE void add(const QByteArray& inputsAsJson) override;
    Q_INVOKABLE QByteArray inputs(const QString& name) const override;
    Q_INVOKABLE QByteArray inputs(const QString& name, const int& roundIndex) const override;

  private:
    typedef QList<InputCandidate> Candidates;
    Candidates fromJson(const QByteArray& json) const;
    // Services
    ServiceCollection* const _services;
};

#endif // DARTSINPUTCONTROLLER_H
