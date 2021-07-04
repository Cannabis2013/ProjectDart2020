#ifndef ICREATEFROMJSON_H
#define ICREATEFROMJSON_H

#include <QByteArray>

template<typename TModel, typename TParams = QByteArray>
class ICreateFromJson
{
public:
    virtual TModel create(const TParams &json) const = 0;
};

#endif // ICREATEINPUTFROMENTITY_H
