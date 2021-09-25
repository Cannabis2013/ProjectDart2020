#ifndef ICREATEPLAYERFROMJSON_H
#define ICREATEPLAYERFROMJSON_H

#include "PlayerModelsContext/SLAs/iplayermodel.h"

class ICreatePlayerFromJson
{
public:
    virtual const PlayersContext::IPlayerModel *createPlayerModel(const QByteArray &json) const = 0;
};

#endif // IDEFAULTPLAYERMODELBUILDER_H
