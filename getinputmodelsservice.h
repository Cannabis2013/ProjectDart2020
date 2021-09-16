#ifndef GETINPUTMODELSSERVICE_H
#define GETINPUTMODELSSERVICE_H

#include "igetinputmodelsservice.h"
#include "iplayerinput.h"
#include "idbcontext.h"

class GetInputModelsService : public IGetInputModelsService
{
public:
    QVector<const IModel<QUuid> *> inputModels(const QUuid &tournamentId, const IModelsDbContext *dbService) const override;
    QVector<const IModel<QUuid>*> inputModels(const QUuid &tournamentId, const int &hint, const IModelsDbContext *dbService) const override;
private:
    QVector<const IModel<QUuid>*> getModels(const QUuid &tournamentId, const QVector<const IModel<QUuid> *> &models) const;
    QVector<const IModel<QUuid>*> getModels(const int &hint, const QVector<const IModel<QUuid> *> &models) const;
};
#endif // GETINPUTMODELSSERVICE_H
