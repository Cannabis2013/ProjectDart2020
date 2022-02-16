#ifndef UPDATEDARTSINDEXES_H
#define UPDATEDARTSINDEXES_H
#include "IndexesSLAs/iupdatedartsindexes.h"
class DartsIndexServices;
template<typename T> class IModel;
class DartsModelsServices;
class UpdateDartsIndexes : public IUpdateDartsIndexes<IModel<QUuid>>
{
public:
    typedef IDbContext<Model> DbContext;
    UpdateDartsIndexes(DartsModelsServices *services);
    void update(const QByteArray &byteAray, const Uuid &tournamentID) const override;
private:
    void updateTournament(IDartsIndex *index, IModel<QUuid> *model) const;
    DartsModelsServices *_services;
    DartsIndexServices *_idxServices;
    DbContext *_dartsDb;
};

#endif // UPDATEDARTSINDEXES_H
