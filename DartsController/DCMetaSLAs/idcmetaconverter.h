#ifndef IDCMETACONVERTER_H
#define IDCMETACONVERTER_H
class QByteArray;
template<typename TMetaModel>
class IDCMetaConverter
{
public:
    typedef TMetaModel Meta;
    typedef QByteArray ByteArray;
    virtual Meta convert(const ByteArray &byteArray) const = 0;
};
#endif // IDCMETACONVERTER_H
