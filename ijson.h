#ifndef IJSON_H
#define IJSON_H

template<typename TJsonFormat>
class IJson
{
public:
    virtual TJsonFormat toJson() const = 0;
};

#endif // IJSONMODELCONVERSION_H
