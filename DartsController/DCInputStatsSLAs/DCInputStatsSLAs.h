#ifndef DCINPUTSTATSSLAS_H
#define DCINPUTSTATSSLAS_H

#include "idcaveragecalc.h"
#include "idcinputavgjsonkeys.h"

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
    IDCInputAvgJsonKeys *inputAvgKeys() const
    {
        return _inputAvgKeys;
    }
    void setInputAvgKeys(IDCInputAvgJsonKeys *service)
    {
        _inputAvgKeys = service;
    }
private:
    IDCAverageCalc *_calcInputAvg;
    IDCInputAvgJsonKeys *_inputAvgKeys;
};
#endif // DCINPUTSTATSSLAS_H
