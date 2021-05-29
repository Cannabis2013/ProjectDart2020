#ifndef IDARTSPOINTJSONASSEMBLERSERVICE_H
#define IDARTSPOINTJSONASSEMBLERSERVICE_H

#include <qvector.h>

namespace DartsPointSingleAttemptContext{
    template<typename  TPointModel,typename TIndexesModel, typename TJsonFormat, typename TUuid>
    class IDartsPointJsonService
    {
    public:
        typedef TIndexesModel DartsIndexes;
        typedef TPointModel PointModel;
        typedef TUuid IdFormat;
        virtual IdFormat getWinnerIdByJson(const TJsonFormat&) const = 0;
        virtual TJsonFormat buildJsonByIndexesAndPoint(const DartsIndexes*,
                                                      const PointModel* pointModel) const = 0;
        virtual TJsonFormat assembleJsonWinnerName(const QString&) const = 0;
    };
}

#endif // IDARTSPOINTJSONASSEMBLERSERVICE_H
