#ifndef BUILDSINGLEATTEMPTPOINTCONTROLLER_H
#define BUILDSINGLEATTEMPTPOINTCONTROLLER_H

#include "ibuildcontrollerservice.h"
#include "idartscontrollerentity.h"
#include <quuid.h>
#include "dartspointlogisticcontroller.h"
#include <dartspointsingleattempt.h>
#include "DartsPointCalculator.h"
#include "pointvalidator.h"
#include "PointIndexController.h"
#include "dartspointjsonservice.h"
#include "dartsplayerpointservice.h"
#include "buildDartsPointTurnValues.h"
#include "dartscontrollerpointbuilder.h"
#include "DartsIndexesBuilderService.h"
#include "dartsplayermodelbuilderservice.h"
#include "dartscontrollerpointmodelsservice.h"
namespace DartsBuilderContext {
    class BuildSingleAttemptPointController : public
            IBuildControllerService<AbstractDartsPointController*,
                                               const IDartsControllerEntity<QUuid,QString>*>
    {
    public:
        ControllerInterface buildController(ControllerDetails details) const override;
    };
}


#endif // BUILDSINGLEATTEMPTPOINTCONTROLLER_H
