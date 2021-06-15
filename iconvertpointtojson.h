#ifndef IDATAMODELPOINTTOJSON_H
#define IDATAMODELPOINTTOJSON_H

#include "idatamodelpoint.h"
#include "qbytearray.h"

namespace DartsDataModelsContext {
    class IConvertPointToJson
    {
    public:
        virtual QByteArray toJson(const IDataModelPoint* model) = 0;
    };
}

#endif // IDATAMODELPOINTTOJSON_H
