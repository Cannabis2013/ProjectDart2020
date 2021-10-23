#ifndef DCINPUTSTATSSLAS_H
#define DCINPUTSTATSSLAS_H
#include "idcscorestats.h"
class DCInputStatsSLAs
{
public:
    IDCScoreStats *statsController() const
    {
        return _statsBuilder;
    }
    void setStatsBuilder(IDCScoreStats *builder)
    {
        _statsBuilder = builder;
    }
private:
    IDCScoreStats *_statsBuilder;
};
#endif // DCINPUTSTATSSLAS_H
