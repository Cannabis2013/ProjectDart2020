#ifndef IDCIDXBUILDER_H
#define IDCIDXBUILDER_H
class TnmVals;
class DCMeta;
class DCIndex;
class IDartsIndex;
class IDCIdxBuilder
{
public:
    virtual TnmVals convert(const DCIndex &idx) const = 0;
};
#endif // IDCIDXBUILDER_H
