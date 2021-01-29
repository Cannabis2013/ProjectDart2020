#include "localplayerdbcontext.h"


bool LocalPlayerDBContext::addModel(const QUuid &key, const IPlayerModel<QUuid, QString> *model)
{
    _models.insert(key.toString(),model);
    return true;
}


bool LocalPlayerDBContext::removeModel(const QUuid &key, const int &)
{
    /*
     * Since all keys are unique, the second parameter is redundant.
     */
    _models.remove(key.toString());
    return true;
}

bool LocalPlayerDBContext::replaceModel(const QUuid &key, const int &, const IPlayerModel<QUuid, QString> *model)
{
    /*
     * Since all keys are unique, the second parameter is redundant.
     */
    _models.replace(key.toString(),model);
    return true;
}


const IPlayerModel<QUuid, QString> *LocalPlayerDBContext::model(const QUuid &key, const int &index)
{
    Q_UNUSED(key);
    auto keys = _models.keys();
    auto indexKey = keys.at(index);
    auto model = _models.value(indexKey);
    return model;
}


int LocalPlayerDBContext::indexOfModel(const QUuid &key, const IPlayerModel<QUuid, QString> *model)
{
    Q_UNUSED(key);
    auto models = _models.values();
    for (int i = 0; i < models.count(); ++i) {
        auto m = models.at(i);
        if(m == model)
            return i;
    }
    return -1;
}


int LocalPlayerDBContext::countOfModels(const QUuid &key)
{
    Q_UNUSED(key);
    auto count = _models.count();
    return count;
}


QVector<const IPlayerModel<QUuid, QString> *> LocalPlayerDBContext::models(const QUuid &)
{
    auto models = _models.values();
    auto vectorList = models.toVector();
    return vectorList;
}
