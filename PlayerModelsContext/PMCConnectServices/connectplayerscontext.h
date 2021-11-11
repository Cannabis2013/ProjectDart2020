#ifndef CONNECTPLAYERMODELSCONTEXT_H
#define CONNECTPLAYERMODELSCONTEXT_H

#include "PlayerModelsContext/PMCConnectSLAs/iconnectplayermodelscontext.h"
class ConnectPlayersContext : public IConnectPlayerModelsContext
{
public:
    virtual void connectServices(AbstractApplicationInterface *application, AbstractPlayersContext *playersContext) override
    {
        QObject::connect(application,&AbstractApplicationInterface::requestCreatePlayer,
                playersContext,&AbstractPlayersContext::createPlayer);
        QObject::connect(playersContext,&AbstractPlayersContext::playerAddedSucces,
                application,&AbstractApplicationInterface::playerAddedSucces);
        QObject::connect(playersContext,&AbstractPlayersContext::playerAddedError,
                application,&AbstractApplicationInterface::playerAddedError);
        QObject::connect(application,&AbstractApplicationInterface::requestPlayers,
                playersContext,&AbstractPlayersContext::handleRequestPlayersDetails);
        QObject::connect(playersContext,&AbstractPlayersContext::sendPlayers,
                application,&AbstractApplicationInterface::sendPlayers);
        QObject::connect(application,&AbstractApplicationInterface::requestDeletePlayers,
                playersContext,&AbstractPlayersContext::deletePlayersFromIndexes);
        QObject::connect(playersContext,&AbstractPlayersContext::playersDeletedStatus,
                application,&AbstractApplicationInterface::playersDeletedStatus);
    }
};

#endif // CONNECTPLAYERMODELSCONTEXT_H
