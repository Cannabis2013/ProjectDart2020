#ifndef IDCCREATEPLAYERSFROMJSON_H
#define IDCCREATEPLAYERSFROMJSON_H

#include "DartsController/DCPlayerSLAs/idcplayerkeys.h"
#include "DartsController/DCPlayerSLAs/idcplayermodelbuilder.h"
class IDCCreatePlayersFromJson
{
public:
    virtual QVector<DCContext::IDCPlayer *> createModels(const QByteArray &json, const IDCPlayerKeys *jsonKeys,
                                                         const IDCPlayerModelBuilder *playerBuilder) const = 0;
};
#endif // IDCCREATEPLAYERSFROMJSON_H
