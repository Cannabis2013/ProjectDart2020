#ifndef IDCCREATEPLAYERSFROMJSON_H
#define IDCCREATEPLAYERSFROMJSON_H

#include "DCPlayerSLAs/idcplayerkeys.h"
#include "DCPlayerSLAs/idcplayermodelbuilder.h"
class IDCCreatePlayersFromJson
{
public:
    virtual QVector<const DCContext::IDCPlayer *> createModels(const QByteArray &json,
                                                               const IDCPlayerKeys *jsonKeys,
                                                               const IDCPlayerModelBuilder *playerBuilder) const = 0;
};
#endif // IDCCREATEPLAYERSFROMJSON_H
