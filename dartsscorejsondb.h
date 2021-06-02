#ifndef DARTSSCOREDB_H
#define DARTSSCOREDB_H

#include "idartsscoredb.h"
#include "abstractjsonpersistence.h"
#include "iunaryservice.h"

namespace DartsModelsContext {
    class DartsScoreJsonDb :
            public IDartsScoreDb,
            private AbstractJSONPersistence
    {
    public:
        typedef IUnaryService<const QJsonObject &, QVector<const IDartsScoreInput*>> JsonExtractor;
        typedef IUnaryService<const QVector<const IDartsScoreInput*>&,QJsonObject> JsonAssembler;
        static DartsScoreJsonDb* createInstance(JsonExtractor* extractor, JsonAssembler* assembler);
        void addModel(const IModel<QUuid,QByteArray>* model) override;
        const IDartsScoreInput *modelByIndex(const int &index) const override;
        const IDartsScoreInput *modelById(const QUuid &id) const override;
        QVector<const IModel<QUuid,QByteArray> *> models() const override;
        bool removeModelByIndex(const int &index) override;
        bool removeModelById(const QUuid &id) override;
        int indexOfModel(const IModel<QUuid,QByteArray>* model) override;
        void replaceModel(const int &index, const IModel<QUuid,QByteArray>* model) override;
        // Json services
        DartsScoreJsonDb* setDartsScoresExtractorService(JsonExtractor *dartsScoresExtractor);
        DartsScoreJsonDb* setDartsScoresJsonAssemblerService(JsonAssembler *dartsScoresJsonAssemblerService);
        void saveState() override;
    private:
        void fetchModels() override;

        JsonExtractor* _jsonExtractorService;
        JsonAssembler* _jsonAssemblerService;
        const QString _fileName = "DartsMultiAttemptScores";
        QVector<const IDartsScoreInput*> _dartsScoreModels;
    };
}

#endif // DARTSSCOREDB_H
