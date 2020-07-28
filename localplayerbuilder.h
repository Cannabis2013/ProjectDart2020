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

private:
    bool _generateUniqueId;
};


class PlayerBuilderParameters : public IPlayerBuilderParameters<QString,QUuid>
{
public:
    QString userName() const override
    {
        return _firstName;
    }
    void setUserName(const QString &value)
    {
        _firstName = value;
    }

    QString eMail() const override
    {
        return _mailAdress;
    }
    void setMailAdress(const QString &value)
    {
        _mailAdress = value;
    }

    int role() const override
    {
        return _role;
    }
    void setRole(int value)
    {
        _role = value;
    }

    QUuid id() const override
    {
        return _id;
    }
    void setId(const QUuid &id)
    {
        _id = id;
    }

private:

    QString _firstName;
    QString _lastName;
    QString _mailAdress;
    QUuid _id;
    int _role;
};

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
        model->setUserName(params.userName());
        model->setEmail(mail);

        if(options.generateUniqueID())
            model->setId(QUuid::createUuid());
        else
            model->setId(params.id());

        return model;
    }
};

#endif // LOCALPLAYERBUILDER_H
