#ifndef ABSTRACTDCIPTCONVERTER_H
#define ABSTRACTDCIPTCONVERTER_H
#include "DartsModelsContext/InputModelsSLAs/abstractdartsinput.h"
#include "abstractdcinputbuilder.h"
#include "dcinput.h"
#include "DartsModelsContext/InputModels/diptvals.h"
class AbstractDCIptConverter
{
public:
    virtual DCInput convert(AbstractDartsInput *input, const int &initRemScore, const DCPlayer &player) const = 0;
    virtual DIptVals convert(DCInput &input) const = 0;
    virtual QVector<DCInput> convert(const QVector<AbstractDartsInput*> &inputs) const = 0;
    AbstractDCInputBuilder *iptBuilder() const {return _iptBuilder;}
    void setIptBuilder(AbstractDCInputBuilder *newIptBuilder) {_iptBuilder = newIptBuilder;}
protected:
    AbstractDCIptConverter(AbstractDCInputBuilder *builder):
        _iptBuilder(builder){}
private:
    AbstractDCInputBuilder *_iptBuilder;
};
#endif // IDCIPTCONVERTER_H
