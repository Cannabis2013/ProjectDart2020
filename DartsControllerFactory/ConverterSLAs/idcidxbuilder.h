#ifndef IDCIDXBUILDER_H
#define IDCIDXBUILDER_H
struct TnmVals;
struct DCMeta;
struct DCIndex;
class IDartsIndex;
class IDCIdxBuilder
{
public:
    virtual TnmVals convert(const DCIndex &idx) const = 0;
};
#endif // IDCIDXBUILDER_H
