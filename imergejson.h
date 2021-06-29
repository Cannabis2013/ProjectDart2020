#ifndef IMERGEJSON_H
#define IMERGEJSON_H
#include <qvector.h>


template<typename TJsonFormat>
class IMergeJson
{
public:
    typedef TJsonFormat Json;
    virtual Json createJsonFromList(const QVector<Json> &json2) const = 0;
};

#endif // ICOMBINEJSONSERVICE_H
