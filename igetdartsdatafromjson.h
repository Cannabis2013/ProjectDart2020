#ifndef IGETDARTSDATAFROMJSON_H
#define IGETDARTSDATAFROMJSON_H

#include <qvector.h>

template<typename TJson, typename TUuid, typename TString, typename TNumeric>
class IGetDartsDataFromJson
{
public:
    typedef TJson Json;
    typedef TNumeric Numeric;
    typedef TUuid Id;
    typedef TString String;
    virtual Id tournamentIdFromJson(const Json &json) const = 0;
    virtual Id winnerIdFromJson(const Json &json) const = 0;
};

#endif // IPLAYERJSONEXTRACTOR_H
