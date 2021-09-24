#ifndef ICREATEPLAYERFROMJSON_H
#define ICREATEPLAYERFROMJSON_H

#include "icreatemodel.h"
#include "PlayerModelsContext/SLAs/iplayermodel.h"

class ICreatePlayerFromJson : public ICreateModel<PlayersContext::IPlayerModel,QByteArray>
{
public:
    virtual const PlayersContext::IPlayerModel *createPlayerModel(const QByteArray &json) const = 0;
};

#endif // IDEFAULTPLAYERMODELBUILDER_H
