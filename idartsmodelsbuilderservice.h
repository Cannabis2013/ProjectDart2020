#ifndef IDARTSSCOREMODELSBUILDERSERVICE_H
#define IDARTSSCOREMODELSBUILDERSERVICE_H

#include <qvector.h>

namespace DartsScoreMultiAttemptContext {
    template<typename TModelsInterface, typename TJsonFormat, typename TScoreModelsService>
    class IDartsModelsBuilderService
    {
    public:
        typedef TScoreModelsService ScoreModelsService;
        typedef TModelsInterface ModelsInterface;
        typedef TJsonFormat JsonFormat;
        virtual const ModelsInterface* buildModelByJson(const JsonFormat& json) const = 0;
        virtual QVector<const ModelsInterface*> buildModelsByJson(const JsonFormat& json) const = 0;
        virtual QVector<const ModelsInterface*> buildModelsByModelsService(const TScoreModelsService* service) const = 0;
    };
}

#endif // IDARTSSCOREMODELSBUILDERSERVICE_H
