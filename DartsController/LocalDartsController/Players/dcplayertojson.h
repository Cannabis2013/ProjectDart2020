#ifndef DCPLAYERTOJSON_H
#define DCPLAYERTOJSON_H

#include <DartsController/Contracts/Converters/idcmodeltojson.h>

struct DCPlayer;

class DCPlayerToJson : public IDCModelToJson<DCPlayer>
{
public:
    virtual QJsonObject convert(const DCPlayer &player) const override;
};
#endif // DCPLAYERTOJSON_H
