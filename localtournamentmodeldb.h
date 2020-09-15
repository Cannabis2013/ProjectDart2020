#ifndef LOCALTOURNAMENTMODELDB_H
#define LOCALTOURNAMENTMODELDB_H

#include <quuid.h>
#include "imodeldbcontext.h"

#include <QMultiHash>

template<class TUuid>
class IModel
{
public:;
    virtual TUuid id() const = 0;
    virtual void setId(const TUuid &val) = 0;

    virtual int type() const = 0;
    virtual void setType(const int &val) = 0;

    virtual void setParent(const TUuid &parent) = 0;
    virtual TUuid parent() const = 0;
};

class LocalTournamentModelDB : public IModelDBContext<IModel<QUuid>,QString>
{
public:
    LocalTournamentModelDB();

    const QStringList acceptedModelTypes = {"TournamentModel", "RoundModel", "SetModel", "ScoreModel"};

    // IModelDBContext interface
    bool addModel(const QString &type, const IModel<QUuid> *model);
    bool removeModel(const QString &type, const int &indexOfModel);
    bool replaceModel(const QString &type, const int &indexOfModel, const IModel<QUuid> *newModel);
    const IModel<QUuid> *model(const QString &type, const int &index);
    int indexOfModel(const QString &type, const IModel<QUuid> *model) const;
    QList<const IModel<QUuid> *> models(const QString &type);

private:
    QMultiHash<QString,const IModel<QUuid>*> *_models;
};
#endif // LOCALTOURNAMENTMODELDB_H
