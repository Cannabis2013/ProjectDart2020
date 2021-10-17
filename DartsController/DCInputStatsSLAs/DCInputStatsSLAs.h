#ifndef DCINPUTSTATSSLAS_H
#define DCINPUTSTATSSLAS_H
#include "idcaveragecalc.h"
class DCInputStatsSLAs
{
public:
    IDCAverageCalc *calcInputAvg() const
    {
        return _calcInputAvg;
    }
    void setCalcInputAvg(IDCAverageCalc *service)
    {
        _calcInputAvg = service;
    }
private:
    IDCAverageCalc *_calcInputAvg;
};
#endif // DCINPUTSTATSSLAS_H
