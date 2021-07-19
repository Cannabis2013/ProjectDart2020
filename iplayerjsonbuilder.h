#ifndef IPLAYERJSONBUILDER_H
#define IPLAYERJSONBUILDER_H

#include <qvector.h>

template<typename TPlayerModel,typename TUuid, typename TString, typename TJson>
class IPlayerJsonBuilder
{
public:
    virtual TJson createJson(const QVector<TUuid> &playerIds, const QVector<TString> &playerNames) const = 0;
    virtual TJson createJson(const TPlayerModel *playerModel) const = 0;
    virtual TJson createJson(const QVector<const TPlayerModel*> &playerModels) const = 0;
};
#endif // ICREATEJSONFROMPLAYERCREDENTIALS_H
