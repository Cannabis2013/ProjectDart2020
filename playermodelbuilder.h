#ifndef LOCALPLAYERBUILDER_H
#define LOCALPLAYERBUILDER_H

#include "iplayermodelbuilder.h"
#include "player.h"
#include <qstring.h>
#include "quuid.h"

#include "playermodelbuildercontext.h"

typedef IPlayerModel<QUuid,QString> DefaultPlayerModelInterface;
typedef IPlayerModelBuilder<DefaultPlayerModelInterface,IPlayerBuilderParameters<QString,QUuid>,IPlayerModelOptions<QUuid>> PlayerBuilder;

class PlayerModelBuilder : public PlayerBuilder
{
public:
    PlayerModelBuilder() {}

    // IDataModelBuilder interface
public:
    DefaultPlayerModelInterface *buildPlayerModel(const IPlayerBuilderParameters<QString,QUuid> &params, const IPlayerModelOptions<QUuid> &options) override
    {
        DefaultPlayerModelInterface* model = new Player();
        auto mail = params.eMail() != "" ? params.eMail() : "defaultsucker@mail.com";
        model->setId(QUuid::createUuid());
        model->setUserName(params.playerName());
        model->setEmail(mail);
        model->setUserRole(params.role());

        if(options.generateID())
            model->setId(QUuid::createUuid());
        else
            model->setId(params.id());

        return model;
    }
};

#endif // LOCALPLAYERBUILDER_H
