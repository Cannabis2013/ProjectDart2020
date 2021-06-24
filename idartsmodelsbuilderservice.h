#ifndef IDARTSSCOREMODELSBUILDERSERVICE_H
#define IDARTSSCOREMODELSBUILDERSERVICE_H

#include <qvector.h>

namespace DartsScoreControllerContext {
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
        virtual const ModelsInterface* createScoreModel(const JsonFormat& json) const = 0;
        virtual const ModelsInterface* createScoreModel(const int& score) const = 0;
        virtual QVector<const ModelsInterface*> createScoreModels(const JsonFormat& json) const = 0;
        virtual QVector<const ModelsInterface*> createScoreModels(const TScoreModelsService* service) const = 0;
    };
}

#endif // IDARTSSCOREMODELSBUILDERSERVICE_H
