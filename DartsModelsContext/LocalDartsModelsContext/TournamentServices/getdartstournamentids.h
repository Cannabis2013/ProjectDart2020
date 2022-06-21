#ifndef GETDARTSTOURNAMENTIDS_H
#define GETDARTSTOURNAMENTIDS_H

#include <quuid.h>
#include <qvector.h>
#include <DartsModelsContext/Contracts/Tournament/igettournamentids.h>

template<typename T> class IDbContext;
template<typename T> class IModel;

class GetDartsIds : public IGetDartsTournamentIds<IModel<QUuid>,IDbContext<IModel<QUuid>>>
{
public:
    virtual QVector<QUuid> get(const QVector<int> &indexes, const IDbContext<BaseModel> *dbContext) const override;
private:
    QVector<QUuid> modelsByIndexes(const QVector<BaseModel*> &models, const QVector<int> &indexes) const;
};

#endif // GETDARTSTOURNAMENTIDS_H
