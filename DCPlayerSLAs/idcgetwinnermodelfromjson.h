#ifndef IDCGETWINNERMODELFROMJSON_H
#define IDCGETWINNERMODELFROMJSON_H

#include "DCPlayerSLAs/idcplayerkeys.h"
#include "DCPlayerSLAs/idcplayermodelbuilder.h"
class IDCGetWinnerModelFromJson
{
public:
    virtual const DCContext::IDCPlayer *toWinnerModel(const QByteArray &json,
                                                      const IDCPlayerKeys *jsonKeys,
                                                      const IDCPlayerModelBuilder *playerBuilder) const = 0;
};
#endif // IDCGETWINNERFROMJSON_H
