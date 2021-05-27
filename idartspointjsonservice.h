#ifndef IDARTSPOINTJSONASSEMBLERSERVICE_H
#define IDARTSPOINTJSONASSEMBLERSERVICE_H

#include "iunaryservice.h"
#include <quuid.h>
#include <qbytearray.h>
#include <qvector.h>
#include <iplayerscoreservice.h>
#include "dartspointmodels.h"
#include "idartscontrollerplayer.h"

namespace DartsPointSingleAttemptContext{
    template<typename  TPointModel,typename TIndexes>
    class IDartsPointJsonService
    {
    public:
        typedef DartsPointInputContext::DartsInputKeyValues KeyInputValues;
        typedef TIndexes DartsIndexes;
        typedef TPointModel PointModel;
        typedef IDartsControllerPlayer<QUuid,QString> ControllerPlayer;
        virtual QVector<const TPointModel*> assembleExtendedInputModelsFromJson(const QByteArray&) const = 0;
        virtual QVector<const ControllerPlayer*> assemblePlayerDetailsStructsFromJson(const QByteArray&) const = 0;
        virtual const ControllerPlayer* assembleWinnerStructFromJson(const QByteArray&) const = 0;
        virtual QByteArray assembleJsonAddPointValues(const DartsIndexes*,
                                                      const QUuid &winnerId,
                                                      const PointModel* pointModel) const = 0;
        virtual QByteArray assembleJsonWinnerName(const QString&) const = 0;
    };
}


#endif // IDARTSPOINTJSONASSEMBLERSERVICE_H
