#ifndef ICREATEMODELFROMSTRING_H
#define ICREATEMODELFROMSTRING_H

#include <qvector.h>

template<typename TModelInterface, typename TStringFormat>
class ICreateModelFromString
{
public:
    virtual const TModelInterface* create(const TStringFormat& json) = 0;
};

#endif // IDATAMODELBUILDER_H
