#ifndef IGETDATAFROMJSON_H
#define IGETDATAFROMJSON_H

#include <qvector.h>

template<typename TJson, typename TUuid, typename TString, typename TNumeric>
class IGetDataFromJson
{
public:
    typedef TJson Json;
    typedef TNumeric Numeric;
    typedef TUuid Id;
    typedef TString String;

    virtual int numeric(const Json &json, const String &key) const = 0;
    virtual QVector<Numeric> numerics(const Json &json, const String &key) const = 0;
    virtual Id id(const Json &json, const String &key) const = 0;
};

#endif // IPLAYERJSONEXTRACTOR_H
