#ifndef DCJSONSERVICES_H
#define DCJSONSERVICES_H
#include "AbstractDCJsonBuilder.h"
class DCJsonServices
{
public:
    AbstractDCJsonBuilder *createJson() const
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
