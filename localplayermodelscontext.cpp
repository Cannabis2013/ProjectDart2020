#include "localplayermodelscontext.h"
LocalPlayerModelsContext::LocalPlayerModelsContext()
{
    _playerBuilder = new LocalPlayerBuilder();
}

QUuid LocalPlayerModelsContext::createPlayer(const QString &userName, const QString &email, const int &role)
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
        return options;
    }());

    _models << model;
    auto playerID = model->id();
    return playerID;
}

void LocalPlayerModelsContext::deletePlayerByUserName(const QString &userName)
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

void LocalPlayerModelsContext::deletePlayerByID(const QUuid &player)
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

void LocalPlayerModelsContext::deletePlayerByEmail(const QString &email)
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

QUuid LocalPlayerModelsContext::playerIDFromUserName(const QString &userName) const
{
    try {
        auto model = getModel(userName);
        return model->id();
    } catch (const char *msg) {
        throw msg;
    }
}

QUuid LocalPlayerModelsContext::playerIDFromIndex(const int &index) const
{
    try {
        auto model = _models.at(index);
        auto modelID = model->id();
        return modelID;
    } catch (...) {
        throw "Model not found";
    }
}

QString LocalPlayerModelsContext::playerUserName(const QUuid &id) const
{
    for (auto model : _models) {
        auto modelID = model->id();
        if(modelID == id)
            return model->userName();
    }

    return QString();
}

QString LocalPlayerModelsContext::playerEMail(const QUuid &id) const
{
    for (auto model : _models) {
        auto modelID = model->id();
        if(modelID == id)
            return model->email();
    }

    return QString();
}

QList<QUuid> LocalPlayerModelsContext::players() const
{
    QList<QUuid> resultingList;
    for (auto model : _models) {
        auto modelID = model->id();
        resultingList << modelID;
    }

    return resultingList;
}

int LocalPlayerModelsContext::playersCount() const
{
    return _models.count();
}

DefaultPlayerBuilder *LocalPlayerModelsContext::playerBuilder() const
{
    return _playerBuilder;
}

PlayerContextInterface *LocalPlayerModelsContext::setPlayerBuilder(DefaultPlayerBuilder *builder)
{
    _playerBuilder = builder;

    return this;
}

void LocalPlayerModelsContext::buildPlayerModel(const QUuid &id, const QString &userName, const QString &email)
{
    auto model = playerBuilder()->buildModel([id,userName,email]
    {
        PlayerBuilderParameters params;
        params.setId(id);
        params.setUserName(userName);
        params.setMailAdress(email);
        return params;
    }(),[]
    {
        PlayerModelOptions options;
        options.setGenerateUniqueId(false);
        return options;
    }());

    _models << model;
}

DefaultPlayerInterface *LocalPlayerModelsContext::getModel(const QString &userName) const
{
    for (auto model : _models) {
        if(model->userName() == userName)
            return model;
    }

    throw "Model not found";
}



