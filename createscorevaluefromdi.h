#ifndef CREATESCOREVALUEFROMDI_H
#define CREATESCOREVALUEFROMDI_H

#include <iqmldatabuilder.h>
#include <qvariant.h>

class CreateScoreValueFromDI : public IQMLDataBuilder<QPair<int,int>,QVariant>
{
public:
    typedef QPair<int,int> PointInput;
    virtual QVariant createItem(const PointInput &d) const override
    {
        return d.second;
    }
};

#endif // CREATESCOREVALUEFROMDI_H
