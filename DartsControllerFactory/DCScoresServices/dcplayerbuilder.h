#ifndef DCPLAYERBUILDER_H
#define DCPLAYERBUILDER_H
#include "ModelBuilderSLAs/idcmodelconverter.h"
class QJsonObject;
class DCPlayer;
class DCPlayerBuilder : public IDCModelConverter<DCPlayer>
{
public:
    virtual Model create(const Json &json) const override;
};

#endif // DCPLAYERBUILDER_H
