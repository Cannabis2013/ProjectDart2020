#ifndef DCPLAYERBUILDER_H
#define DCPLAYERBUILDER_H
#include "Converters/idcjsontomodel.h"
class QJsonObject;
class DCPlayer;
class DCPlayerBuilder : public IDCJsonToModel<DCPlayer>
{
public:
    virtual DCPlayer convert(const QJsonObject &json) const override;
};

#endif // DCPLAYERBUILDER_H
