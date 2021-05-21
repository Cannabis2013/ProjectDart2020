#ifndef IJSONMODELCONVERSION_H
#define IJSONMODELCONVERSION_H

template<typename TJsonFormat>
class IJsonModelsService
{
public:
    virtual TJsonFormat toJson() const = 0;
};

#endif // IJSONMODELCONVERSION_H
