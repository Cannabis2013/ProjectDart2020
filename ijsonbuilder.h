#ifndef IJSONBUILDER_H
#define IJSONBUILDER_H


template<typename TJsonFormat, typename TUuid, typename TString>
class IJsonBuilder
{
public:
    typedef TString String;
    typedef TUuid Id;
    typedef TJsonFormat JsonFormat;
    virtual JsonFormat createJsonByKey(const Id &id, const String &key) const = 0;
    virtual JsonFormat createJsonByKey(const String &string, const String &key) const = 0;

};
#endif // IDARTSJSONEXTRACTOR_H
