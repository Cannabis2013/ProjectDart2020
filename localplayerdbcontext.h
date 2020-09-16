#ifndef LOCALPLAYERDBCONTEXT_H
#define LOCALPLAYERDBCONTEXT_H

#include "iplayermodel.h"
#include "imodeldbcontext.h"
#include "qlist.h"
#include <quuid.h>
#include <QMultiHash>
#include <qlist.h>

class LocalPlayerDBContext : public IModelDBContext<IPlayerModel<QUuid,QString>,QUuid>
{
public:
    // IModelDBContext interface
public:
    bool addModel(const QUuid &key, const IPlayerModel<QUuid,QString> *model);
    bool removeModel(const QUuid &key, const int &);
    bool replaceModel(const QUuid &key, const int &, const IPlayerModel<QUuid,QString> *model);
    const IPlayerModel<QUuid,QString> *model(const QUuid &key, const int &index);
    int indexOfModel(const QUuid &key, const IPlayerModel<QUuid,QString> *model);
    int countOfModels(const QUuid &key);
    QList<const IPlayerModel<QUuid,QString> *> models(const QUuid &);

private:
    QMultiHash<QString,const IPlayerModel<QUuid,QString>*> _models;
};

#endif // LOCALPLAYERDBCONTEXT_H
