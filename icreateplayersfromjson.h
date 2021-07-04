#ifndef ICREATEPLAYERSFROMJSON_H
#define ICREATEPLAYERSFROMJSON_H

#include "iplayermodel.h"
#include <qvector.h>
#include "icreatefromjson.h"
class ICreatePlayersFromJson : public ICreateFromJson<QVector<const DartsModelsContext::IPlayerModel*>>
{
public:
    virtual QVector<const DartsModelsContext::IPlayerModel*> create(const QByteArray &json) const override = 0;
};

#endif // ICREATEPLAYERFROMJSON_H
