#ifndef CONNECTDARTSSCORECONTROLLER_H
#define CONNECTDARTSSCORECONTROLLER_H

#include "iternaryservice.h"
#include "abstractdartsscorecontroller.h"
#include "AbstractApplicationInterface.h"
#include "abstractmodelsservice.h"

class ConnectDartsScoreController :
        public ITernaryService<AbstractDartsScoreController*,
                               AbstractApplicationInterface*,
                               AbstractModelsService*,
                               AbstractDartsScoreController*>
{

public:
    AbstractDartsScoreController* service(AbstractDartsScoreController*controller,
                                          AbstractApplicationInterface*application,
                                          AbstractModelsService*modelsService) override;
};

#endif // CONNECTDARTSSCORECONTROLLER_H
