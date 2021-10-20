#ifndef DCINPUTSTATSSLAS_H
#define DCINPUTSTATSSLAS_H
#include "idcstatsbuilder.h"
class DCInputStatsSLAs
{
public:
    IDCStatsBuilder *statsBuilder() const
    {
        return _statsBuilder;
    }
    void setStatsBuilder(IDCStatsBuilder *builder)
    {
        _statsBuilder = builder;
    }
private:
    IDCStatsBuilder *_statsBuilder;
};
#endif // DCINPUTSTATSSLAS_H
