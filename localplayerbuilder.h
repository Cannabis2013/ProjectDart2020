#ifndef LOCALPLAYERBUILDER_H
#define LOCALPLAYERBUILDER_H

#include "idatamodelbuilder.h"
#include "player.h"
#include <qstring.h>
#include "quuid.h"

#include "iplayerbuildercontext.h"

typedef IPlayerModel<QUuid,QString> DefaultModelInterface;
typedef IPlayerBuilderParameters<QString,QUuid> DefaultParameters;
typedef IDataModelBuilder<DefaultModelInterface,DefaultParameters,IPlayerBuilderConfiguration> DefaultPlayerBuilder;

class LocalPlayerBuilder : public DefaultPlayerBuilder
{
public:
    LocalPlayerBuilder() {}

    // IDataModelBuilder interface
public:
    DefaultModelInterface *buildModel(const DefaultParameters &params, const IPlayerBuilderConfiguration &options) override
    {
        DefaultModelInterface* model = new Player();
        auto mail = params.eMail() != "" ? params.eMail() : "defaultsucker@mail.com";
        model->setId(QUuid::createUuid());
        model->setUserName(params.playerName());
        model->setEmail(mail);
        model->setUserRole(params.role());

        if(options.generateUniqueID())
            model->setId(QUuid::createUuid());
        else
            model->setId(params.id());

        return model;
    }
};

#endif // LOCALPLAYERBUILDER_H
