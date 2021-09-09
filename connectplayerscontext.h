#ifndef CONNECTPLAYERMODELSCONTEXT_H
#define CONNECTPLAYERMODELSCONTEXT_H

#include "iconnectplayermodelscontext.h"
class ConnectPlayersContext : public IConnectPlayerModelsContext
{
public:
    virtual void connectServices(AbstractApplicationInterface *application, IPlayerModelsContext *playersContext) override
    {
        QObject::connect(application,&AbstractApplicationInterface::requestCreatePlayer,
                playersContext,&IPlayerModelsContext::createPlayer);
        QObject::connect(playersContext,&IPlayerModelsContext::playerAddedSucces,
                application,&AbstractApplicationInterface::playerAddedSucces);
        QObject::connect(playersContext,&IPlayerModelsContext::playerAddedError,
                application,&AbstractApplicationInterface::playerAddedError);
        QObject::connect(application,&AbstractApplicationInterface::requestPlayers,
                playersContext,&IPlayerModelsContext::handleRequestPlayersDetails);
        QObject::connect(playersContext,&IPlayerModelsContext::sendPlayers,
                application,&AbstractApplicationInterface::sendPlayers);
        QObject::connect(application,&AbstractApplicationInterface::requestDeletePlayers,
                playersContext,&IPlayerModelsContext::deletePlayersFromIndexes);
        QObject::connect(playersContext,&IPlayerModelsContext::playersDeletedStatus,
                application,&AbstractApplicationInterface::playersDeletedStatus);
    }
};

#endif // CONNECTPLAYERMODELSCONTEXT_H
