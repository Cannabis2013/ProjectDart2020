#ifndef DCCONVERTINPUTS_H
#define DCCONVERTINPUTS_H
#include "ModelsConverterSLAs/idcmodelsconverter.h"
class QJsonObject;
class DCInput;
class DCConvertInputs : public IDCModelsConverter<DCInput>
{
public:
    Models convert(const QByteArray &byteArray, ModelBuilder *builder) const override;
};
#endif // DCCONVERTINPUTS_H
