#ifndef DCPLAYERBUILDER_H
#define DCPLAYERBUILDER_H
#include "ModelBuilderSLAs/idcjsontomodel.h"
class QJsonObject;
class DCPlayer;
class DCPlayerBuilder : public IDCJsonToModel<DCPlayer>
{
public:
    virtual Model create(const Json &json) const override;
};

#endif // DCPLAYERBUILDER_H
