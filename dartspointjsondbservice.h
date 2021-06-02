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
        typedef QVector<const IModel<QUuid,QByteArray>*> PlayerInputs;
        typedef IUnaryService<const QJsonArray &, PlayerInputs> JsonExtractor;
        typedef IUnaryService<const PlayerInputs&,QJsonArray> JsonAssembler;
        static DartsPointJsonDbService* createInstance(JsonExtractor* extractor, JsonAssembler* assembler);
        void fetchModels() override;
        void saveState() override;
        void addModel(const IModel<QUuid,QByteArray>* model) override;
        const IModel<QUuid,QByteArray> *getModelByIndex(const int &index) const override;
        QVector<const IModel<QUuid,QByteArray>*> models() const override;
        bool removeModelByIndex(const int &index) override;
        bool removeModelById(const QUuid&id) override;
        int indexOfModel(const IModel<QUuid,QByteArray>* score) override;
        void replaceModel(const int &index, const IModel<QUuid,QByteArray>* point) override;
        const IModel<QUuid,QByteArray> *modelById(const QUuid &id) const override;
        const IModel<QUuid,QByteArray> *modelByIndex(const int&index) const override;
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
