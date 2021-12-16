#ifndef ICOUNTINPUTMODELS_H
#define ICOUNTINPUTMODELS_H
template<typename T>
class IDbContext;
template<typename T>
class IModel;
class QUuid;
template<typename TDbCtx>
class ICountInputModels
{
public:
    typedef TDbCtx DbCtx;
    virtual int count(const QUuid& tournamentId,const DbCtx* service) const = 0;
};

#endif // IINPUTMODELSCOUNTSERVICE_H
