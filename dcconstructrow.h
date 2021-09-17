#ifndef DCCONSTRUCTROW_H
#define DCCONSTRUCTROW_H

#include "constructtargetrow.h"
#include "idcmetainfo.h"
#include "dartsboundaries.h"
#include "dartsfieldvalues.h"
#include "dartsthreshold.h"
#include "dartscreateterminaldivisor.h"
#include "dartscreateterminalthreshold.h"
#include "dartsdivisors.h"
#include "dartsterminaldivisor.h"
class DCConstructRow : public ConstructTargetRow
{
public:
    static DCConstructRow *createInstance(const DCBuilding::IDCMetaInfo *meta)
    {
        return new DCConstructRow(meta);
    }
private:
    DCConstructRow(const DCBuilding::IDCMetaInfo *meta)
    {
        setBoundariesService(new DartsBoundaries);
        setFieldValuesService(new DartsFieldValues);
        setDivisorsService(new DartsDivisors);
        setThresholdsService(new DartsThresholds(DartsCreateTerminalThreshold(new DartsBoundaries)));
        setTerminalDivisor(new DartsTerminalDivisor(DartsCreateTerminalDivisor(new DartsDivisors)));
    }
};
#endif // DPCCONSTRUCTROW_H
