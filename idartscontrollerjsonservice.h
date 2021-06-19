#ifndef IDARTSCONTROLLERJSONSERVICE_H
#define IDARTSCONTROLLERJSONSERVICE_H

#include <qvector.h>

namespace DartsPointControllerContext{
    template<typename  TPointModel,typename TIndexesModel, typename TJsonFormat, typename TUuid>
    class IDartscontrollerJsonService
    {
    public:
        typedef TIndexesModel DartsIndexes;
        typedef TPointModel PointModel;
        typedef TUuid IdFormat;
        virtual IdFormat getWinnerIdByJson(const TJsonFormat&) const = 0;
        virtual TJsonFormat convertDartsIndexesToJson(const DartsIndexes* indexes) const = 0;
        virtual TJsonFormat convertDartsModelToJson(const PointModel* pointModel) const = 0;
        virtual TJsonFormat assembleJsonWinnerName(const QString&) const = 0;
    };
}

#endif // IDARTSPOINTJSONASSEMBLERSERVICE_H
