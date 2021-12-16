#ifndef ABSTRACTDCIPTCONVERTER_H
#define ABSTRACTDCIPTCONVERTER_H
#include "abstractdcinputbuilder.h"
template<typename T>
class QVector;
struct DIptVals;
class AbstractDCIptConverter
{
public:
    virtual DCInput convert(const DIptVals &input, const int &initRemScore, const DCPlayer &player) const = 0;
    virtual DIptVals convert(DCInput &input) const = 0;
    virtual QVector<DCInput> convert(const QVector<DIptVals> &inputs) const = 0;
    AbstractDCInputBuilder *iptBuilder() const {return _iptBuilder;}
    void setIptBuilder(AbstractDCInputBuilder *newIptBuilder) {_iptBuilder = newIptBuilder;}
protected:
    AbstractDCIptConverter(AbstractDCInputBuilder *builder):
        _iptBuilder(builder){}
private:
    AbstractDCInputBuilder *_iptBuilder;
};
#endif // IDCIPTCONVERTER_H
