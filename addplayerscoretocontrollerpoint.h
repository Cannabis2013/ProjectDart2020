#ifndef ADDPLAYERSCORETOCONTROLLERPOINT_H
#define ADDPLAYERSCORETOCONTROLLERPOINT_H

#include "ibinaryservice.h"
#include "dartscontrollerpoint.h"

namespace DartsPointSingleAttemptContext{
    typedef IDartsControllerPoint<QUuid,QString,QByteArray> IControllerPoint;
    typedef IBinaryService<const int&, const IControllerPoint*,void> IAddPlayerScoreService;
    class AddPlayerScoreToControllerPoint : public IAddPlayerScoreService
    {
    public:
        void service(const int& playerScore, const IControllerPoint* point) override
        {
            auto nonConstModel = const_cast< IControllerPoint*>(point);
            auto typeInferedModel = dynamic_cast<DartsControllerPoint*>(nonConstModel);
            typeInferedModel->setAccumulatedScore(playerScore);
        }
    };
}

#endif // ADDPLAYERSCORETOCONTROLLERPOINT_H
