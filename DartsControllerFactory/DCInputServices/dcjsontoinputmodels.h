#ifndef DCJSONTOINPUTMODELS_H
#define DCJSONTOINPUTMODELS_H
#include "ModelsConverterSLAs/idcjsontomodels.h"
class QJsonObject;
class DCInput;
class DCJsonToInputModels : public IDCJsonToModels<DCInput>
{
public:
    Models convert(const QByteArray &byteArray, ModelBuilder *builder) const override;
};
#endif // DCJSONTOINPUTMODELS_H
