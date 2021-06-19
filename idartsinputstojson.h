#ifndef IDARTSINPUTSTOJSON_H
#define IDARTSINPUTSTOJSON_H

#include <qvector.h>

template<typename TModelInterface, typename TJsonFormat>
class IDartsInputsToJson
{
public:
    typedef TModelInterface InputModel;
    typedef QVector<const InputModel*> InputModels;
    typedef TJsonFormat JsonFormat;
    virtual JsonFormat toJson(const InputModels &inputs) const = 0;
};

#endif // IDARTSINPUTSTOJSON_H
