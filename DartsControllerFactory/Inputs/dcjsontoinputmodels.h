#ifndef DCJSONTOINPUTMODELS_H
#define DCJSONTOINPUTMODELS_H
#include "Converters/idcjsontomodels.h"
class QJsonObject;
class DCInput;
class DCJsonToInputModels : public IDCJsonToModels<DCInput>
{
public:
    Models convert(const QByteArray &byteArray, JsonToModel *jsonToModel) const override;
};
#endif // DCJSONTOINPUTMODELS_H
