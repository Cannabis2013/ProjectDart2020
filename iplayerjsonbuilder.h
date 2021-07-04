#ifndef IPLAYERJSONBUILDER_H
#define IPLAYERJSONBUILDER_H

#include <qvector.h>

template<typename TPlayerModel,typename TUuid, typename TString, typename TJson>
class IPlayerJsonBuilder
{
public:
    typedef TPlayerModel Player;
    typedef TUuid Id;
    typedef TString String;
    typedef TJson Json;
    virtual Json createJson(const QVector<Id> &playerIds, const QVector<String> &playerNames) const = 0;
    virtual Json createJson(const Id &playerId,const String &playerName) const = 0;
    virtual Json createJson(const QVector<const Player*> &playerModels) const = 0;
};
#endif // ICREATEJSONFROMPLAYERCREDENTIALS_H
