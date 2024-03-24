#ifndef DARTSSTATISTICS_H
#define DARTSSTATISTICS_H

#include "istatsreport.h"
#include <QObject>

class ServiceCollection;
class DartsInput;
class IScoresCalculator;
class IDartsIndexes;
class IDartsScores;
class IDartsInputs;
class IDartsPlayers;
class QJsonArray;
class QJsonObject;
class QString;

class DartsStatistics : public QObject, public IStatsReport {
        Q_OBJECT
public:
        DartsStatistics(ServiceCollection* services);
        Q_INVOKABLE QByteArray playerOne() const override;
        Q_INVOKABLE QByteArray playerTwo() const override;

private:
        // Private member methods
        QJsonObject playerReport(const QString& name) const;

        // Services
        ServiceCollection* const _services;
};

#endif // DARTSSTATISTICS_H
