#ifndef GETDARTSSCOREFROMDB_H
#define GETDARTSSCOREFROMDB_H

#include "igetdartsscorefromdb.h"
#include "idartsscoreinput.h"
namespace DartsModelsContext {
    class GetDartsScoreFromDb : public IGetDartsScoreFromDb
    {
    public:
        virtual const IPlayerInput *get(const QUuid &tournamentId, const QUuid &playerId,
                                        const int &roundIndex, const IDartsInputDb *dbService) const override;
    private:
        const IPlayerInput *getModelThatMatchesParameters(const QVector<const IPlayerInput*> &models,
                                                             const QUuid &tournamentId, const QUuid &playerId,
                                                             const int &roundIndex) const;
        bool matchParameters(const IPlayerInput*,const QUuid &tournamentId, const QUuid &playerId,
                                 const int &roundIndex) const;
    };
}

#endif // GETDARTSSCOREMODELFROMDB_H
