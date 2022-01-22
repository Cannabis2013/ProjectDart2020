#ifndef DCPLAYERBUILDER_H
#define DCPLAYERBUILDER_H
#include "ModelBuilderSLAs/idcmodelbuilder.h"
class QJsonObject;
class DCPlayer;
class DCPlayerBuilder : public IDCModelBuilder<DCPlayer,QJsonObject>
{
public:
    virtual Model create(const Json &json) const override;
};

#endif // DCPLAYERBUILDER_H
