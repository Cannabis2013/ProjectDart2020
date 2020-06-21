#ifndef LOCALPLAYERBUILDER_H
#define LOCALPLAYERBUILDER_H

#include "idatamodelbuilder.h"
#include "player.h"
#include <qstring.h>
#include "quuid.h"

class PlayerModelOptions
{
public:
    bool generateUniqueId;
    bool customUuid = false;
};

class PlayerBuilderParameters
{
public:
    QString firstName;
    QString lastName;
    QString mailAdress;

    int role;
};

typedef IPlayerModel<QUuid,QString> DefaultModelInterface;

class LocalPlayerBuilder : public IDataModelBuilder<DefaultModelInterface,PlayerBuilderParameters,PlayerModelOptions>
{
public:
    LocalPlayerBuilder() {}

    // IDataModelBuilder interface
public:
    DefaultModelInterface *buildModel(const PlayerBuilderParameters &args, const PlayerModelOptions &options) override
    {
        DefaultModelInterface* model = new Player();

        model->setId(QUuid::createUuid());

        model->setFirstName(args.firstName);
        model->setLastName(args.lastName);
        model->setEmail(args.mailAdress);

        // TODO: Missing model type type

        return model;
    }
};

#endif // LOCALPLAYERBUILDER_H
