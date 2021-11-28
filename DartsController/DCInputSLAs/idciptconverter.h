#ifndef IDCIPTCONVERTER_H
#define IDCIPTCONVERTER_H
#include "DartsModelsContext/InputModelsSLAs/abstractdartsinput.h"
#include "dciptvals.h"
#include "DartsModelsContext/InputModels/diptvals.h"
class IDCIptConverter
{
public:
    virtual DCIptVals convert(AbstractDartsInput *input) const = 0;
    virtual DIptVals convert(DCIptVals &input) const = 0;
    virtual QVector<DCIptVals> convert(const QVector<AbstractDartsInput*> &inputs) const = 0;
};
#endif // IDCIPTCONVERTER_H
