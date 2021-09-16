#ifndef DPCCONSTRUCTROW_H
#define DPCCONSTRUCTROW_H

#include "constructtargetrow.h"

#include "dartsattempts.h"
#include "idcmetainfo.h"
#include "dartsboundaries.h"
#include "dartsfieldvalues.h"
#include "dartsthreshold.h"
#include "dartscreateterminaldivisor.h"
#include "dartscreateterminalthreshold.h"
#include "dartsdivisors.h"
#include "dartsterminaldivisor.h"
class DPCConstructRow : public ConstructTargetRow
{
public:
    static DPCConstructRow *createInstance(const DCBuilding::IDCMetaInfo *meta)
    {
        return new DPCConstructRow(meta);
    }
private:
    DPCConstructRow(const DCBuilding::IDCMetaInfo *meta)
    {
        setAttemptsService(new DartsAttempts(meta));
        setBoundariesService(new DartsBoundaries);
        setFieldValuesService(new DartsFieldValues);
        setDivisorsService(new DartsDivisors);
        setThresholdsService(new DartsThresholds(DartsCreateTerminalThreshold(meta, new DartsBoundaries)));
        setTerminalDivisor(new DartsTerminalDivisor(DartsCreateTerminalDivisor(meta,new DartsDivisors)));
    }
};

#endif // DPCCONSTRUCTROW_H
