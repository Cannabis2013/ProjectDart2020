#ifndef DCSETTOURNAMENTID_H
#define DCSETTOURNAMENTID_H

#include "DCMetaSLAs/idcsettournamentid.h"

class DCSetTournamentId : public IDCSettournamentId
{
public:
    virtual void setId(QJsonObject &obj, const QUuid &tournamentId) const override
    {
        obj["tournamentId"] = tournamentId.toString(QUuid::WithoutBraces);
    }
};
#endif // DCSETTOURNAMENTID_H
