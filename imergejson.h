#ifndef IMERGEJSON_H
#define IMERGEJSON_H

template<typename TJsonFormat>
class IMergeJson
{
public:
    virtual void mergeIntoJson(TJsonFormat &json1, const TJsonFormat &json2) const = 0;
};

#endif // ICOMBINEJSONSERVICE_H
