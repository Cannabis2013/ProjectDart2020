#ifndef IDCGETWINNERMODELFROMJSON_H
#define IDCGETWINNERMODELFROMJSON_H

#include "ijsonkeyplayer.h"
#include "idcplayermodelbuilder.h"
class IDCGetWinnerModelFromJson
{
public:
    virtual const DCContext::IDCPlayer *toWinnerModel(const QByteArray &json,
                                                      const IJsonKeysPlayer *jsonKeys,
                                                      const IDCPlayerModelBuilder *playerBuilder) const = 0;
};
#endif // IDCGETWINNERFROMJSON_H
