#ifndef COUNTDARTSINPUTS_H
#define COUNTDARTSINPUTS_H

#include <qvector.h>
#include <quuid.h>
#include <DartsModelsContext/InputSLAs/icountinputmodels.h>

class CountDartsInputs : public ICountInputModels<IDbContext<IModel<QUuid>>>
{
public:
    virtual int count(const QUuid &tournamentId, const DbCtx *dbService) const override;
private:
    QVector<const IModel<QUuid>*> getInputModels(const QUuid &tournamentId, const DbCtx *dbService) const;
};
#endif // INPUTMODELSCOUNTSERVICE_H
