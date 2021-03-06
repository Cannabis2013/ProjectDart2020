#ifndef DARTSPOINTDBSERVICE_H
#define DARTSPOINTDBSERVICE_H

#include "abstractjsonpersistence.h"
#include "idartspointdb.h"
#include "idartspointinput.h"
#include <quuid.h>
#include "iunaryservice.h"

namespace DartsModelsContext
{
    class DartsPointJsonDbService :
            public IDartsPointDb,
            public AbstractJSONPersistence
    {
    public:
        typedef QVector<const IDartsInput*> PlayerInputs;
        typedef IUnaryService<const QJsonArray &, PlayerInputs> JsonExtractor;
        typedef IUnaryService<const PlayerInputs&,QJsonArray> JsonAssembler;
        static DartsPointJsonDbService* createInstance(JsonExtractor* extractor, JsonAssembler* assembler);
        void fetchModels() override;
        void saveState() override;
        void addModel(const IDartsInput* model) override;
        const IDartsInput *getModelByIndex(const int &index) const override;
        QVector<const IDartsInput*> models() const override;
        bool removeModelByIndex(const int &index) override;
        bool removeModelById(const QUuid&id) override;
        int indexOfModel(const IDartsInput* score) override;
        void replaceModel(const int &index, const IDartsInput* point) override;
        const IDartsInput *modelById(const QUuid &id) const override;
        const IDartsInput *modelByIndex(const int&index) const override;
        // Set service methods
        DartsPointJsonDbService* setDartsPointsExtractorService(JsonExtractor *dartsPointsExtractor);
        DartsPointJsonDbService* setDartsPointsJsonAssemblerService(JsonAssembler* dartsSingleAttemptPointInputAssembler);

    private:
        // Services
        JsonExtractor* _dartsPointsExtractor;
        JsonAssembler* _dartsPointsJsonAssemblerService;
        const QString _fileName = "DartsPoints";
        PlayerInputs _dartsPointModels;
    };
}


#endif // DARTSPOINTDBSERVICE_H
