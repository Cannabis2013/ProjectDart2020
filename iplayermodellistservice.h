#ifndef IPLAYERDBLISTSERVICE_H
#define IPLAYERDBLISTSERVICE_H

#include <qvector.h>

template<typename TModel,typename TUuid, typename TString>
class IPlayerModelListService
{
public:
    typedef TModel Model;
    typedef TUuid Id;
    typedef TString String;
    virtual QVector<Id> createPlayerIds(const QVector<const Model*> &models) const = 0;
    virtual QVector<String> createPlayerNames(const QVector<const Model*> &models) const = 0;
};

#endif // ICREATEPLAYERDATASERVICE_H
