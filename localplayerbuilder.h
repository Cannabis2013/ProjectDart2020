#ifndef LOCALPLAYERBUILDER_H
#define LOCALPLAYERBUILDER_H

#include "idatamodelbuilder.h"
#include "player.h"
#include <qstring.h>
#include "quuid.h"

#include "iplayerbuildercontext.h"

typedef IPlayerModel<QUuid,QString> DefaultModelInterface;
typedef IPlayerBuilderParameters<QString> DefaultParameters;
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

        model->setId(QUuid::createUuid());

        model->setFirstName(params.firstName());
        model->setLastName(params.lastName());
        model->setEmail(params.eMail());

        if(options.generateUniqueID() && !options.generateCustomID())
            model->setId(QUuid::createUuid());

        return model;
    }
};

#endif // LOCALPLAYERBUILDER_H
