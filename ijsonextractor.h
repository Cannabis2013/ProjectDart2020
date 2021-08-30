#ifndef IJSONEXTRACTOR_H
#define IJSONEXTRACTOR_H

template<typename TJson, typename TUuid, typename TString>
class IJsonExtractor
{
public:
    virtual TUuid getIdValueByKey(const TJson &json, const TString &key) const = 0;
    virtual TString getStringValueByKey(const TJson& json, const TString &key) const = 0;
    virtual int getIntegerValueByKey(const TJson& json, const TString &key) const = 0;
};

#endif // IJSONEXTRACTOR_H
