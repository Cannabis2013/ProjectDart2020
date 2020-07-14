#ifndef LOCALPLAYERBUILDER_H
#define LOCALPLAYERBUILDER_H

#include "idatamodelbuilder.h"
#include "player.h"
#include <qstring.h>
#include "quuid.h"

#include "iplayerbuildercontext.h"

class PlayerModelOptions : public IPlayerBuilderConfiguration
{
public:
    bool generateUniqueID() const override
    {
        return _generateUniqueId;
    }
    void setGenerateUniqueId(bool generateUniqueId)
    {
        _generateUniqueId = generateUniqueId;
    }

    bool generateCustomID() const override
    {
        return _customUuid;
    }
    void setCustomUuid(bool customUuid)
    {
        _customUuid = customUuid;
    }

private:
    bool _generateUniqueId;
    bool _customUuid = false;
};


class PlayerBuilderParameters : public IPlayerBuilderParameters<QString>
{
public:
    QString firstName() const
    {
        return _firstName;
    }
    void setFirstName(const QString &value)
    {
        _firstName = value;
    }

    QString lastName() const
    {
        return _lastName;
    }
    void setLastName(const QString &value)
    {
        _lastName = value;
    }

    QString eMail() const
    {
        return _mailAdress;
    }
    void setMailAdress(const QString &value)
    {
        _mailAdress = value;
    }

    int role() const
    {
        return _role;
    }
    void setRole(int value)
    {
        _role = value;
    }

private:

    QString _firstName;
    QString _lastName;
    QString _mailAdress;

    int _role;
};

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
