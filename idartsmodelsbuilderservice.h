#ifndef IDARTSSCOREMODELSBUILDERSERVICE_H
#define IDARTSSCOREMODELSBUILDERSERVICE_H

#include <qvector.h>

namespace DartsScoreMultiAttemptContext {
    template<typename TModelsInterface,
             typename TJsonFormat,
             typename TScoreModelsService,
             typename TUuid,
             typename TString>
    class IDartsModelsBuilderService
    {
    public:
        typedef TUuid IdFormat;
        typedef TString StringFormat;
        typedef TScoreModelsService ScoreModelsService;
        typedef TModelsInterface ModelsInterface;
        typedef TJsonFormat JsonFormat;
        virtual const ModelsInterface* buildModelByJson(const JsonFormat& json) const = 0;
        virtual QVector<const ModelsInterface*> buildModelsByJson(const JsonFormat& json) const = 0;
        virtual QVector<const ModelsInterface*> buildModelsByModelsService(const TScoreModelsService* service) const = 0;
        virtual const ModelsInterface* buildModelByValues(const int& score,
                                                          const IdFormat& playerId,
                                                          const StringFormat& playerName,
                                                          const IdFormat& tournamentId) const = 0;
    };
}

#endif // IDARTSSCOREMODELSBUILDERSERVICE_H
