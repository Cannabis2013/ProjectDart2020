#ifndef IDARTSPOINTJSONASSEMBLERSERVICE_H
#define IDARTSPOINTJSONASSEMBLERSERVICE_H

#include <qvector.h>

namespace DartsPointSingleAttemptContext{
    template<typename  TPointModel,typename TIndexesModel, typename TPlayerModel, typename TJsonFormat>
    class IDartsPointJsonService
    {
    public:
        typedef TIndexesModel DartsIndexes;
        typedef TPointModel PointModel;
        typedef TPlayerModel ControllerPlayer;
        virtual QVector<const TPointModel*> buildDartsControllerPointByJson(const TJsonFormat&) const = 0;
        virtual QVector<const ControllerPlayer*> assemblePlayerDetailsStructsFromJson(const TJsonFormat&) const = 0;
        virtual const ControllerPlayer* assembleWinnerStructFromJson(const TJsonFormat&) const = 0;
        virtual TJsonFormat buildJsonByIndexesAndPoint(const DartsIndexes*,
                                                      const PointModel* pointModel) const = 0;
        virtual TJsonFormat assembleJsonWinnerName(const QString&) const = 0;
    };
}

#endif // IDARTSPOINTJSONASSEMBLERSERVICE_H
