#ifndef GETDARTSSCOREFROMDB_H
#define GETDARTSSCOREFROMDB_H

#include "igetdartsscorefromdb.h"
#include "idartsscoreinput.h"
namespace ModelsContext {
    class GetDartsScoreFromDb : public IGetDartsScoreFromDb
    {
    public:
        virtual const IModel<QUuid> *get(const QUuid &tournamentId, const QUuid &playerId,
                                        const int &roundIndex, const IDbService *dbService) const override;
    private:
        const IModel<QUuid> *getModelThatMatchesParameters(const QVector<const IModel<QUuid> *> &models,
                                                             const QUuid &tournamentId, const QUuid &playerId,
                                                             const int &roundIndex) const;
        bool matchParameters(const IModel<QUuid> *, const QUuid &tournamentId, const QUuid &playerId,
                                 const int &roundIndex) const;
    };
}

#endif // GETDARTSSCOREMODELFROMDB_H
