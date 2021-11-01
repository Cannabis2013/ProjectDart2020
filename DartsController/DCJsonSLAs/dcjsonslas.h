#ifndef DCJSONSLAS_H
#define DCJSONSLAS_H
#include "AbstractDCJsonBuilder.h"
class DCJsonSLAs
{
public:
    AbstractDCJsonBuilder *jsonBuilder() const
    {
        return _jsonResponseBuilder;
    }
    void setJsonResponseBuilder(AbstractDCJsonBuilder *newJsonResponseBuilder)
    {
        _jsonResponseBuilder = newJsonResponseBuilder;
    }
private:
    AbstractDCJsonBuilder *_jsonResponseBuilder;
};
#endif // DSJSONSERVICES_H
