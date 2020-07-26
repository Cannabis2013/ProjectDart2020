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
    QString userName() const
    {
        return _firstName;
    }
    void setUserName(const QString &value)
    {
        _firstName = value;
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
        auto mail = params.eMail() != "" ? params.eMail() : "defaultsucker@mail.com";
        model->setId(QUuid::createUuid());
        model->setUserName(params.userName());
        model->setEmail(mail);

        if(options.generateUniqueID() && !options.generateCustomID())
            model->setId(QUuid::createUuid());

        return model;
    }
};

#endif // LOCALPLAYERBUILDER_H
