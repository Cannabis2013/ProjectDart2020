#ifndef IDCGETWINNERMODELFROMJSON_H
#define IDCGETWINNERMODELFROMJSON_H

#include "DartsController/DCPlayerSLAs/idcplayerkeys.h"
#include "DartsController/DCPlayerSLAs/idcplayerbuilder.h"
class IDCGetWinnerModelFromJson
{
public:
    virtual DCPlayer toWinnerModel(const QByteArray &json, const IDCPlayerKeys *jsonKeys,
                                   const IDCPlayerBuilder *playerBuilder) const = 0;
};
#endif // IDCGETWINNERFROMJSON_H
