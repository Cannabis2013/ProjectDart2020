#ifndef CONNECTDARTSSINGLESCORECONTROLLER_H
#define CONNECTDARTSSINGLESCORECONTROLLER_H

#include "iconnectdartsscorecontroller.h"

class ConnectDartsMultiAttemptController : public IConnectDartsScoreController
{
public:
    void connectController(AbstractDartsController* controller,
                           AbstractApplicationInterface* application,
                           AbstractModelsService* modelsService) override;
};

#endif // CONNECTDARTSSINGLESCORECONTROLLER_H
