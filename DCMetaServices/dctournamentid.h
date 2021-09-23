#ifndef DCTOURNAMENTID_H
#define DCTOURNAMENTID_H

#include "DCMetaSLAs/idctournamentid.h"

class DCTournamentId : public IDCTournamentId
{
public:
    static DCTournamentId *createInstance(const QUuid &id)
    {
        return new DCTournamentId(id);
    }
    virtual QUuid id() const override
    {
        return _id;
    }
private:
    DCTournamentId(const QUuid &id):
        _id(id){}
    const QUuid _id;
};

#endif // DCTOURNAMENTID_H
