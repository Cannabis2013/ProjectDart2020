#ifndef IDARTSCONTROLLERJSONSERVICE_H
#define IDARTSCONTROLLERJSONSERVICE_H

#include <qvector.h>

namespace DartsPointControllerContext{
    template<typename  TPointModel, typename TIndexesModel, typename TJsonFormat, typename TUuid>
    class IDartscontrollerJsonService
    {
    public:
        typedef TIndexesModel DartsIndexes;
        typedef TPointModel PointModel;
        typedef TUuid IdFormat;
        typedef TJsonFormat JsonFormat;
        virtual IdFormat getWinnerIdByJson(const JsonFormat&) const = 0;
        virtual JsonFormat createJsonByDartsPoint(const PointModel* pointModel) const = 0;
        virtual JsonFormat createJsonByWinnerName(const QString&) const = 0;
        virtual JsonFormat createJsonByTournamentId(const IdFormat &tournamentId) const = 0;
    };
}

#endif // IDARTSPOINTJSONASSEMBLERSERVICE_H
