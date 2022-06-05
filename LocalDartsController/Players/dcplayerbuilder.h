#ifndef DCPLAYERBUILDER_H
#define DCPLAYERBUILDER_H

#include <DartsController/Converters/idcjsontomodel.h>

class QJsonObject;
struct DCPlayer;

class DCPlayerBuilder : public IDCJsonToModel<DCPlayer>
{
public:
    virtual DCPlayer convert(const QJsonObject &json) const override;
};

#endif // DCPLAYERBUILDER_H
