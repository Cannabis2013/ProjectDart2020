#ifndef IDCINDEXTOBYTEARRAY_H
#define IDCINDEXTOBYTEARRAY_H
class QByteArray;
struct DCMeta;
struct DCIndex;
class IDartsIndex;
class IDCIndexToByteArray
{
public:
    typedef QByteArray ByteArray;
    virtual ByteArray convert(const DCIndex &idx) const = 0;
};
#endif // IDCIDXBUILDER_H
