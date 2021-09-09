#ifndef IDCCREATEPLAYERSFROMJSON_H
#define IDCCREATEPLAYERSFROMJSON_H

#include "ijsonkeyplayer.h"
#include <idcplayermodelbuilder.h>
class IDCCreatePlayersFromJson
{
public:
    virtual QVector<const DCContext::IDCPlayer *> createModels(const QByteArray &json,
                                                               const IJsonKeysPlayer *jsonKeys,
                                                               const IDCPlayerModelBuilder *playerBuilder) const = 0;
};
#endif // IDCCREATEPLAYERSFROMJSON_H
