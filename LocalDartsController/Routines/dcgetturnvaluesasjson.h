#ifndef DCGETTURNVALUESASJSON_H
#define DCGETTURNVALUESASJSON_H

#include <DartsController/Routines/idcgetturnvaluesasjson.h>

class QJsonObject;
class IDCFinishBuilder;
template<typename T,typename U>
class IDCPlayerManager;
class QString;
struct DCPlayer;
template<typename T,typename U> class IDCIndexController;
struct DCInput;
struct DCMeta;
struct DCIndex;
class DCServices;

class DCGetTurnValuesAsJson : public IDCGetTurnValuesAsJson
{
public:
    typedef IDCIndexController<DCIndex,DCMeta> IndexController;
    typedef IDCPlayerManager<DCPlayer,DCInput> PlayerManager;
    DCGetTurnValuesAsJson(DCServices *services);
    virtual QByteArray toJson() const override;
private:
    QJsonObject toJson(const DCIndex &index, const DCPlayer &player, const QString &finish) const;
    QByteArray toByteArray(const QJsonObject &json) const;
    IndexController *_indexController;
    PlayerManager *_playerManager;
    IDCFinishBuilder *_createFinishes;
};

#endif // DCGETTURNVALUESASJSON_H
