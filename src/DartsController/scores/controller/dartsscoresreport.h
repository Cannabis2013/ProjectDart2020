#ifndef DARTSSCORESREPORT_H
#define DARTSSCORESREPORT_H

#include "iscoresreport.h"

#include <QObject>

class IDartsFinishes;
class IDartsIndexes;
class ServiceCollection;
class IDartsScores;

class DartsScoresReport : public QObject, public IScoresReport {
        Q_OBJECT
public:
        DartsScoresReport(ServiceCollection* services);
        QString initialScore() const override;
        Q_INVOKABLE int playerOne() const override;
        Q_INVOKABLE int playerTwo() const override;
        Q_INVOKABLE QString finishRow() const override;
        Q_INVOKABLE QString delta() const override;

private:
        IDartsScores* const _scores;
        IDartsIndexes* const _indexes;
        IDartsFinishes* const _finishes;
};

#endif // DARTSSCORESREPORT_H
