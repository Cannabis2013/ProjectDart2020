#ifndef DARTSTURNREPORT_H
#define DARTSTURNREPORT_H

class IDartsPlayers;
class IDartsIndexes;

class QJsonObject;

class DartsTurnReport {
public:
        DartsTurnReport(IDartsPlayers* players, IDartsIndexes* indexes);

        QJsonObject report() const;

private:
        // Services
        IDartsPlayers* const _players;
        IDartsIndexes* const _indexes;
};

#endif // DARTSTURNREPORT_H
