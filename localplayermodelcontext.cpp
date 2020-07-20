#include "localplayermodelcontext.h"
LocalPlayerModelContext::LocalPlayerModelContext()
{
    _playerBuilder = new LocalPlayerBuilder();
}

QUuid LocalPlayerModelContext::createPlayer(const QString &userName, const QString &email, const int &role)
{
    auto model = playerBuilder()->buildModel([userName,email,role]
    {
        PlayerBuilderParameters params;

        params.setUserName(userName);
        params.setMailAdress(email);
        params.setRole(role);

        return params;
    }(),[]
    {
        PlayerModelOptions options;

        options.setGenerateUniqueId(true);
        options.setGenerateUniqueId(false);

        return options;
    }());

    _models << model;

    return model->id();
}

void LocalPlayerModelContext::deletePlayerByUserName(const QString &userName)
{
    for (auto model : _models) {
        auto uName = model->userName();
        if(uName == userName)
        {
            _models.removeOne(model);
            return;
        }
    }

    throw "No model found with given id";
}

void LocalPlayerModelContext::deletePlayerByID(const QUuid &player)
{
    for (auto model : _models) {
        auto modelID = model->id();
        if(modelID == player)
        {
            _models.removeOne(model);
            return;
        }
    }

    throw "No model found with given id";
}

void LocalPlayerModelContext::deletePlayerByEmail(const QString &email)
{
    for (auto model : _models) {
        auto mailAdress = model->email();
        if(mailAdress == email)
        {
            _models.removeOne(model);
            return;
        }
    }

    throw "No model found with given mail adress";
}

QUuid LocalPlayerModelContext::playerIDFromUserName(const QString &userName) const
{
    try {
        auto model = getModel(userName);
        return model->id();
    } catch (const char *msg) {
        throw msg;
    }
}

QUuid LocalPlayerModelContext::playerIDFromIndex(const int &index) const
{
    try {
        auto model = _models.at(index);
        auto modelID = model->id();
        return modelID;
    } catch (...) {
        throw "Model not found";
    }
}

QString LocalPlayerModelContext::playerUserName(const QUuid &id) const
{
    for (auto model : _models) {
        auto modelID = model->id();
        if(modelID == id)
            return model->userName();
    }

    return QString();
}

QString LocalPlayerModelContext::playerEMail(const QUuid &id) const
{
    for (auto model : _models) {
        auto modelID = model->id();
        if(modelID == id)
            return model->email();
    }

    return QString();
}

QList<QUuid> LocalPlayerModelContext::players() const
{
    QList<QUuid> resultingList;
    for (auto model : _models) {
        auto modelID = model->id();
        resultingList << modelID;
    }

    return resultingList;
}

int LocalPlayerModelContext::playersCount() const
{
    return _models.count();
}

DefaultPlayerBuilder *LocalPlayerModelContext::playerBuilder() const
{
    return _playerBuilder;
}

PlayerContextInterface *LocalPlayerModelContext::setPlayerBuilder(DefaultPlayerBuilder *builder)
{
    _playerBuilder = builder;

    return this;
}

DefaultPlayerInterface *LocalPlayerModelContext::getModel(const QString &userName) const
{
    for (auto model : _models) {
        if(model->userName() == userName)
            return model;
    }

    throw "Model not found";
}



