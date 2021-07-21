#ifndef ICREATEPLAYERSFROMJSON_H
#define ICREATEPLAYERSFROMJSON_H

#include "iplayermodel.h"
#include <qvector.h>
#include "icreatefromjson.h"
class ICreatePlayersFromJson : public ICreateFromJson<QVector<const IModel<QUuid>*>>
{
public:
    virtual QVector<const IModel<QUuid>*> create(const QByteArray &json) const override = 0;
};

#endif // ICREATEPLAYERFROMJSON_H
