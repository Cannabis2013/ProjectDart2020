#ifndef IGETINPUTS_H
#define IGETINPUTS_H

template<typename T>
class QVector;
class QUuid;
template<typename T>
class IDbContext;
class IDartsIndex;
struct DartsMetaModel;

template<typename TModel, typename TIndex, typename TMeta>
class IGetInputs
{
public:
    typedef TModel Model;
    typedef QVector<Model*> Models;
    typedef TIndex Index;
    typedef TMeta Meta;
    virtual Model *get(const Meta &meta, const Index *index, const Models &models) const = 0;
    virtual Models get(const QUuid& tournamentId, const Models &models) const = 0;
    virtual Models getHidden(const QUuid& tournamentId, const Models &models) const = 0;
    virtual Models getDisplayed(const QUuid& tournamentId, const Models &models) const = 0;
};
#endif // IGETINPUTMODELSSERVICE_H
