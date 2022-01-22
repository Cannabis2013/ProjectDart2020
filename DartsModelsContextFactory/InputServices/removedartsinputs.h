#ifndef REMOVEDARTSINPUTS_H
#define REMOVEDARTSINPUTS_H
#include "InputsDbSLAs/iremovedartsinputs.h"
template<typename T>
class IModel;
class QUuid;
class RemoveDartsInputs : public IRemoveDartsInputs<IModel<QUuid>>
{
public:
    enum ModelDisplayHint{
        HiddenHint = 0x1,
        DisplayHint = 0x2,
        allHints = HiddenHint | DisplayHint
    };
    virtual void removeInputsById(const QUuid &id, DbContext *dbContext) const override;
    virtual void removeInputsByTournamentId(const QUuid &tournamentId, DbContext *dbContext) const override;
    virtual void removeByTournamentIds(const QVector<QUuid> &tournamentIds, DbContext *dbContext) const override;
    virtual void removeHidden(const QUuid &tournamentId, DbContext *dbContext) const override;
    virtual void removeDisplayed(const QUuid &tournamentId, DbContext *dbContext) const override;
private:
    void removeModel(IModel<QUuid> *model, const QUuid &tournamentId, const int &hint, DbContext *dbContext) const;
    bool removeModel(IModel<QUuid> *inputModel, const QUuid &id, DbContext *dbContext) const;
};
#endif // DEFAULTDBMANIPULATORSERVICE_H
