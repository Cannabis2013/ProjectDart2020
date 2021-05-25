#ifndef ADDPLAYERNAMETOCONTROLLERPOINT_H
#define ADDPLAYERNAMETOCONTROLLERPOINT_H

#include "ibinaryservice.h"
#include "dartscontrollerpoint.h"

namespace DartsPointSingleAttemptContext{
    typedef IDartsControllerPoint<QUuid,QString,QByteArray> IControllerPoint;
    typedef IBinaryService<const QString&, const IControllerPoint*,void> IAddPlayerNameService;
    class AddPlayerNameToControllerPoint : public IAddPlayerNameService
    {
    public:
        void service(const QString& playerName, const IControllerPoint* point) override
        {
            auto nonConstModel = const_cast< IControllerPoint*>(point);
            auto typeInferedModel = dynamic_cast<DartsControllerPoint*>(nonConstModel);
            typeInferedModel->setPlayerName(playerName);
        }
    };
}

#endif // ADDPLAYERNAMETOCONTROLLERPOINT_H
