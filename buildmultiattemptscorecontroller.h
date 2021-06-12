#ifndef BUILDMULTIATTEMPTSCORECONTROLLER_H
#define BUILDMULTIATTEMPTSCORECONTROLLER_H

#include "ibuildcontrollerservice.h"
#include "dartsscorecontroller.h"
#include "idartscontrollerentity.h"
#include "dartsscorelogisticcontroller.h"
#include "ScoreValidator.h"
#include "dartsplayerscoreservice.h"
#include "dartsscorejsonbuilderservice.h"
#include "dartsscoremodelsbuilderservice.h"
#include "dartsscoreindexesbuilderservice.h"
#include "scoreindexcontroller.h"
#include "determinecontrollerstatebywinnerid.h"
#include "addaccumulatedscoretodartsscore.h"
#include "assembledartsscoreturnvalues.h"
#include "DartsScoreJsonExtractor.h"
#include "dartsplayerbuilderservice.h"


namespace DartsBuilderContext {
    class BuildMultiAttemptScoreController : public
            IBuildControllerService<AbstractDartsScoreController*,
                                    const DartsBuilderContext::IDartsControllerEntity<QUuid,QString>*>
    {
    public:
        ControllerInterface buildController(ControllerDetails details) const override;
    };
}

#endif // BUILDMULTIATTEMPTSCORECONTROLLER_H
