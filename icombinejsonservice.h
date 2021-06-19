#ifndef ICOMBINEJSONSERVICE_H
#define ICOMBINEJSONSERVICE_H

template<typename TJsonFormat>
class ICombineJsonService
{
public:
    virtual TJsonFormat combineJson(const TJsonFormat &json1, const TJsonFormat &json2) const = 0;
};

#endif // ICOMBINEJSONSERVICE_H
