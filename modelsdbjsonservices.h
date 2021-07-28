#ifndef MODELSDBJSONSERVICES_H
#define MODELSDBJSONSERVICES_H

#include <icreatejsonfrommodels.h>
#include <icreatemodelsfromjson.h>

class ModelsDbJsonServices
{
public:
    ICreateModelsFromJson *createModelsFromJson() const
    {
        return _createModelsFromJson;
    }
    void setCreateModelsFromJson(ICreateModelsFromJson *newCreateModelsFromJson)
    {
        _createModelsFromJson = newCreateModelsFromJson;
    }

    ICreateJsonFromModels *createJsonFromModels() const
    {
        return _createJsonFromModels;
    }
    void setCreateJsonFromModels(ICreateJsonFromModels *newCreateJsonFromModels)
    {
        _createJsonFromModels = newCreateJsonFromModels;
    }

private:
    ICreateModelsFromJson *_createModelsFromJson;
    ICreateJsonFromModels *_createJsonFromModels;
};

#endif // MODELSDBJSONSERVICES_H
