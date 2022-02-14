#ifndef DCPLAYERTOJSON_H
#define DCPLAYERTOJSON_H
#include "Converters/idcmodeltojson.h"
class DCPlayer;
class DCPlayerToJson : public IDCModelToJson<DCPlayer>
{
public:
    virtual QJsonObject convert(const DCPlayer &player) const override;
};
#endif // DCPLAYERTOJSON_H
