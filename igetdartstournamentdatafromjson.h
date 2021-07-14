#ifndef IGETDARTSTOURNAMENTDATAFROMJSON_H
#define IGETDARTSTOURNAMENTDATAFROMJSON_H

#include "igetdartsdatafromjson.h"
#include "quuid.h"

class IGetDartsTournamentDataFromJson : public IGetDartsDataFromJson<QByteArray, QUuid,QString,int>
{};

#endif // IDEFAULTPLAYERJSONEXTRACTOR_H
