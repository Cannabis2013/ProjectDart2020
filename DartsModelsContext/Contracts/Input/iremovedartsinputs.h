#ifndef IREMOVEDARTSINPUTS_H
#define IREMOVEDARTSINPUTS_H

#include <DartsModelsContext/Contracts/Db/idbcontext.h>
#include <quuid.h>

template <typename TModel>
class IRemoveDartsInputs {
public:
      typedef TModel Model;
      typedef QVector<Model *> Models;
      typedef IDbContext<Model> DbContext;
      virtual void removeInputsById(const QUuid &id,
                                    DbContext *dbContext) const = 0;
      virtual void removeInputsByTournamentId(const QUuid &tournamentId,
                                              DbContext *dbContext) const = 0;
      virtual void removeByTournamentIds(const QVector<QUuid> &tournamentIds,
                                         DbContext *dbContext) const = 0;
      virtual void removeHidden(const QUuid &tournamentId,
                                DbContext *dbContext) const = 0;
      virtual void removeDisplayed(const QUuid &tournamentId,
                                   DbContext *dbContext) const = 0;
};
#endif // IREMOVEINPUTSFROMDB_H
