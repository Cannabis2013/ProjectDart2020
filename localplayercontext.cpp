#include "localplayercontext.h"
LocalPlayerContext::LocalPlayerContext()
{

}

QUuid LocalPlayerContext::createPlayer(const QString &firstName, const QString &lastName, const QString &email, const int &role)
{
    auto model = playerBuilder()->buildModel([firstName,lastName,email,role]
    {
        PlayerBuilderParameters params;

        params.setFirstName(firstName);
        params.setLastName(lastName);
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

void LocalPlayerContext::deletePlayerByFirstName(const QString &firstName)
{
    for (auto model : _models) {
        auto fName = model->firstName();
        if(fName == firstName)
        {
            _models.removeOne(model);
            return;
        }
    }

    throw "No model found with given id";
}

void LocalPlayerContext::deletePlayerByID(const QUuid &player)
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

void LocalPlayerContext::deletePlayerByEmail(const QString &email)
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

QUuid LocalPlayerContext::playerIDFromFullName(const QString &fullName) const
{
    auto indexOfSpaceLeft = fullName.lastIndexOf(32);
    auto indexOfSpaceRight = fullName.count() - indexOfSpaceLeft;

    auto firstName = fullName.left(indexOfSpaceLeft);
    auto lastName = fullName.right(indexOfSpaceRight - 1);

    try {
        auto model = getModel(firstName,lastName);
        return model->id();
    } catch (const char *msg) {
        throw msg;
    }
}

QString LocalPlayerContext::playerFirstName(const QUuid &id) const
{
    for (auto model : _models) {
        auto modelID = model->id();
        if(modelID == id)
            return model->firstName();
    }

    return QString();
}

QString LocalPlayerContext::playerLastName(const QUuid &id) const
{
    for (auto model : _models) {
        auto modelID = model->id();
        if(modelID == id)
            return model->lastName();
    }

    return QString();
}

QString LocalPlayerContext::playerEMail(const QUuid &id) const
{
    for (auto model : _models) {
        auto modelID = model->id();
        if(modelID == id)
            return model->email();
    }

    return QString();
}

QString LocalPlayerContext::playerFullName(const QUuid &id) const
{
    for (auto model : _models) {
        auto modelID = model->id();
        if(modelID == id)
            return model->firstName() + " " + model->lastName();
    }

    return QString();
}

QList<QUuid> LocalPlayerContext::players() const
{
    QList<QUuid> resultingList;
    for (auto model : _models) {
        auto modelID = model->id();
        resultingList << modelID;
    }

    return resultingList;
}

int LocalPlayerContext::playerCount() const
{
    return _models.count();
}

DefaultPlayerBuilder *LocalPlayerContext::playerBuilder() const
{
    return _playerBuilder;
}

PlayerContextInterface *LocalPlayerContext::setPlayerBuilder(DefaultPlayerBuilder *builder)
{
    _playerBuilder = builder;

    return this;
}

DefaultPlayerInterface *LocalPlayerContext::getModel(const QString &firstName, const QString &lastName) const
{
    for (auto model : _models) {
        if(model->firstName() == firstName && model->lastName() == lastName)
            return model;
    }

    throw "Model not found";
}



