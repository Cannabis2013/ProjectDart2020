#ifndef IJSONEXTRACTOR_H
#define IJSONEXTRACTOR_H

template<typename TJson, typename TUuid, typename TString>
class IJsonExtractor
{
public:
    typedef TString String;
    typedef TUuid Id;
    typedef TJson Json;
    virtual String getStringValueByKey(const Json& json, const String &key) const = 0;
    virtual int getIntegerValueByKey(const Json& json, const String &key) const = 0;
};

#endif // IJSONEXTRACTOR_H
