#ifndef DARTSSCORESREPORT_H
#define DARTSSCORESREPORT_H

#include "iscorescontroller.h"
#include <QObject>

class IDartsFinishes;
class IDartsIndexes;
class ServiceCollection;
class IDartsRemainings;

class DartsScoresController : public QObject, public IScoresController {
        Q_OBJECT
public:
    DartsScoresController(ServiceCollection* services);
    Q_INVOKABLE QList<int> all() const override;
    Q_INVOKABLE int current() const override;
    Q_INVOKABLE QString finishRow() const override;

private:
        ServiceCollection* _services;
};

#endif // DARTSSCORESREPORT_H
