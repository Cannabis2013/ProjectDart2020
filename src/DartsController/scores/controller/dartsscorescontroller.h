#ifndef DARTSSCORESREPORT_H
#define DARTSSCORESREPORT_H

#include "iscorescontroller.h"
#include <QObject>

class IDartsFinishes;
class IDartsIndexes;
class ServiceCollection;
class IDartsScores;

class DartsScoresController : public QObject, public IScoresController {
        Q_OBJECT
public:
        DartsScoresController(ServiceCollection* services);
        Q_INVOKABLE int playerOne() const override;
        Q_INVOKABLE int playerTwo() const override;
        Q_INVOKABLE QString finishRow() const override;
        Q_INVOKABLE QString delta() const override;

private:
        ServiceCollection* _services;
};

#endif // DARTSSCORESREPORT_H
