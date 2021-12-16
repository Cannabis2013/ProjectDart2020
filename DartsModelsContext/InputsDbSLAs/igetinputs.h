#ifndef IGETINPUTS_H
#define IGETINPUTS_H
template<typename T>
class QVector;
class QUuid;
template<typename T>
class IDbContext;
class IDartsIndex;
class DartsMetaModel;
template<typename TBaseModel, typename TSuperModel>
class IGetInputs
{
public:
    typedef TBaseModel Model;
    typedef TSuperModel SuperModel;
    virtual SuperModel *get(const DartsMetaModel &meta, const IDartsIndex *index, const IDbContext<Model> *dbContext) const = 0;
    virtual QVector<SuperModel*> get(const QUuid& tournamentId, const IDbContext<Model> *dbService) const = 0;
    virtual QVector<SuperModel*> get(const QUuid& tournamentId, const int& hint, const IDbContext<Model> *dbService) const = 0;
};
#endif // IGETINPUTMODELSSERVICE_H
