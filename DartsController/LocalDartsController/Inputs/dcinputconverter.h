#ifndef DCINPUTCONVERTER_H
#define DCINPUTCONVERTER_H

#include <DartsController/Contracts/Inputs/idcinputconverter.h>

struct DCInput;

class DCInputConverter : public IDCInputConverter<DCInput>
{
public:
    virtual Model convert(const QJsonObject &json) const override;
    virtual QJsonObject convert(const Model &model) const override;
};

#endif // DCINPUTCONVERTER_H
