#ifndef MODELSDBJSONSLAS_H
#define MODELSDBJSONSLAS_H

#include "ModelsContext/MCJsonSLAs/icreatejsonfrommodels.h"
#include "ModelsContext/MCJsonSLAs/icreatemodelsfromjson.h"

class ModelsDbJsonSLAs
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

#endif // MODELSDBJSONSLAS_H
