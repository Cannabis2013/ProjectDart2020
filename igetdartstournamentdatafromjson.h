#ifndef IGETDARTSTOURNAMENTDATAFROMJSON_H
#define IGETDARTSTOURNAMENTDATAFROMJSON_H

#include "igetdatafromjson.h"
#include "quuid.h"

class IGetDartsTournamentDataFromJson : public IGetDataFromJson<QByteArray, QUuid,QString,int>
{};

#endif // IDEFAULTPLAYERJSONEXTRACTOR_H
