#ifndef DARTSSTATUSREPORT_H
#define DARTSSTATUSREPORT_H

#include "src/DartsController/jsonReport/istatusreport.h"
class IDartsStatus;
class IDartsPlayers;
class IDartsIndexes;
class QJsonObject;

class DartsStatusReport : public IStatusReport {
public:
        DartsStatusReport(IDartsPlayers* players, IDartsIndexes* indexes, IDartsStatus* status);

        QJsonObject report() const override;

private:
        // Services
        IDartsPlayers* const _players;
        IDartsIndexes* const _indexes;
        IDartsStatus* const _status;
};

#endif // DARTSSTATUSREPORT_H
