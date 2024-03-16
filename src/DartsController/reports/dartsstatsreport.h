#ifndef DARTSSTATSREPORT_H
#define DARTSSTATSREPORT_H

#include "istatsreport.h"

#include <QObject>

class ServiceCollection;
template <typename T>
class QList;
class Input;
class IScoresCalculator;
class IDartsIndexes;
class IDartsScores;
class IDartsInputs;
class IDartsPlayers;
class QJsonArray;
class QJsonObject;
class QString;

class DartsStatsReport : public QObject, public IStatsReport {
        Q_OBJECT
public:
        DartsStatsReport(ServiceCollection* services);
        Q_INVOKABLE QByteArray playerOne() const override;
        Q_INVOKABLE QByteArray playerTwo() const override;

private:
        // Private member methods
        QJsonObject playerReport(const QString& name) const;
        QList<Input> getInputs(const QString& name) const;
        double average(int initialScore, int score, int count) const;
        int lowest(const QList<Input>& inputs) const;
        int highest(const QList<Input>& inputs) const;

        // Services
        IDartsInputs* const _inputs;
        IDartsScores * const _scores;
        IDartsIndexes* const _indexes;
        IScoresCalculator* const _calculator;
        IDartsPlayers* const _players;
};

#endif // DARTSSTATSREPORT_H
