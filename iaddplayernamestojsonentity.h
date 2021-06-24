#ifndef IADDPLAYERNAMESTOJSONENTITY_H
#define IADDPLAYERNAMESTOJSONENTITY_H

#include "iplayerpointservice.h"
#include "idartscontrollerpoint.h"
#include <qvector.h>
#include "idartscontrollerpoint.h"
#include "idartscontrollerplayer.h"

namespace DartsPointControllerContext {
    template<typename TJsonFormat>
    class IAddPlayerNamesToJsonEntity
    {
    public:
        typedef TJsonFormat JSonFormat;
        typedef IDartsControllerPoint<QUuid,QString,QByteArray> IControllerPoint;
        typedef IDartsControllerPlayer<QUuid,QString,QByteArray> ControllerPlayer;
        typedef IPlayerPointService<ControllerPlayer,IControllerPoint> PlayerService ;
        typedef IDartsControllerPoint<QUuid,QString,JSonFormat> ControllerPoint;
        virtual void addPlayerNamesToJson(JSonFormat &json, const PlayerService* playerService) const = 0;
    };
}
#endif // IADDPLAYERNAMESTOJSONENTITY_H
