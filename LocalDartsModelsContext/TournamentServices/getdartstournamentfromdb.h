#ifndef GETDARTSTOURNAMENTFROMDB_H
#define GETDARTSTOURNAMENTFROMDB_H

#include <quuid.h>
#include <qvector.h>
#include <DartsModelsContext/TournamentsDbSLAs/igetdartstournament.h>

template<typename T> class IModel;

class GetDartsTournamentFromDb : public IGetDartsTournament<IModel<QUuid>>
{
public:
    virtual Model *get(const QUuid &tournamentId, const Models &models) const override;
private:
    Model *findModel(const QUuid &tournamentId, const Models &models) const;
};
#endif // GETDARTSTOURNAMENTDATA_H
