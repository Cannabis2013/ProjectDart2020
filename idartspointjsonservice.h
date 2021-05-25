#ifndef IDARTSPOINTJSONASSEMBLERSERVICE_H
#define IDARTSPOINTJSONASSEMBLERSERVICE_H

#include "iunaryservice.h"
#include <quuid.h>
#include <qbytearray.h>
#include <qvector.h>
#include <iplayerscoreservice.h>
#include "dartspointmodels.h"

namespace DartsPointSingleAttemptContext{
    template<typename TIndexes>
    class IDartsPointJsonService
    {
    public:
        typedef DartsPointInputContext::DartsInputKeyValues KeyInputValues;
        typedef DartsPointInputContext::DartsPointModel ExtendedInputValues;
        typedef DartsPointInputContext::DartsInputPlayerDetails PlayerDetailsStruct;
        virtual QVector<const ExtendedInputValues*> assembleExtendedInputModelsFromJson(const QByteArray&) const = 0;
        virtual QVector<const PlayerDetailsStruct*> assemblePlayerDetailsStructsFromJson(const QByteArray&) const = 0;
        virtual const PlayerDetailsStruct* assembleWinnerStructFromJson(const QByteArray&) const = 0;
        virtual QByteArray assembleJsonAddPointValues(const QUuid&,
                                                      const int&,
                                                      const int&,
                                                      const int&,
                                                      const QUuid&,
                                                      const QUuid&,
                                                      const int&,
                                                      const int&,
                                                      const int&) const = 0;
        virtual QByteArray assembleJsonWinnerName(const QString&) const = 0;
    };
}


#endif // IDARTSPOINTJSONASSEMBLERSERVICE_H
