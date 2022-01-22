#ifndef IDCMETACONVERTER_H
#define IDCMETACONVERTER_H
template<typename TMetaModel, typename TJsonFormat>
class IDCMetaConverter
{
public:
    typedef TMetaModel Meta;
    typedef TJsonFormat Json;
    virtual Meta convert(const Json &byteArray, Meta &meta) const = 0;
};
#endif // IDCMETACONVERTER_H
