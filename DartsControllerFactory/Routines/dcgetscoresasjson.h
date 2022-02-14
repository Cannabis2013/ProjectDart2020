#ifndef DCGETSCORESASJSON_H
#define DCGETSCORESASJSON_H
#include "Routines/idcgetscoresasjson.h"

template<typename T> class IDCModelToJson;
class QJsonArray;
class QJsonObject;
template<typename T,typename U> class IDCPlayerManager;
class DCInput;
class DCPlayer;
class DCServices;
class DCGetScoresAsJson : public IDCGetScoresAsJson
{
public:
    typedef IDCPlayerManager<DCPlayer,DCInput> PlayerManager;
    typedef IDCModelToJson<DCPlayer> PlayerToJson;
    DCGetScoresAsJson(DCServices *services);
    virtual QByteArray get() const override;
private:
    QByteArray toByteArray(const QJsonArray &arr) const;
    PlayerManager *_playerManager;
    PlayerToJson *_playerToJson;
};

#endif // DCGETPLAYERSASJSON_H
