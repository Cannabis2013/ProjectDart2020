#ifndef LOCALTOURNAMENTMODELDB_H
#define LOCALTOURNAMENTMODELDB_H

#include <quuid.h>
#include <QMultiHash>
#include "imodelsdbcontext.h"
#include "modelbuildercollection.h"


class LocalTournamentModelDB : public ImodelsDBContext<IModel<QUuid>,QString>
{
public:
    LocalTournamentModelDB();

    const QStringList acceptedModelTypes = {"Tournament", "Round", "Set", "Score"};

    // IModelDBContext interface
    bool addModel(const QString &type, const IModel<QUuid> *model);
    bool removeModel(const QString &type, const int &indexOfModel);
    bool replaceModel(const QString &type, const int &indexOfModel, const IModel<QUuid> *newModel);
    const IModel<QUuid> *model(const QString &type, const int &index);
    int indexOfModel(const QString &type, const IModel<QUuid> *model);
    int countOfModels(const QString &type);
    QList<const IModel<QUuid> *> models(const QString &type);

private:
    QMultiHash<QString,const IModel<QUuid>*> _models;
};
#endif // LOCALTOURNAMENTMODELDB_H
