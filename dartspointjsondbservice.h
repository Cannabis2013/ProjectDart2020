#ifndef DARTSPOINTDBSERVICE_H
#define DARTSPOINTDBSERVICE_H

#include "abstractjsonpersistence.h"
#include "idartspointdb.h"
#include "idartspointinput.h"
#include <quuid.h>
#include "iunaryservice.h"
class DartsPointJsonDbService :
        public IDartsPointDb,
        public AbstractJSONPersistence
{
public:
    typedef IUnaryService<const QJsonArray &, QVector<const DartsModelsContext::IDartsPointInput *>> JsonExtractor;
    typedef IUnaryService<const QVector<const DartsModelsContext::IDartsPointInput*>&,QJsonArray> JsonAssembler;
    static DartsPointJsonDbService* createInstance(JsonExtractor* extractor, JsonAssembler* assembler);
    void fetchModels() override;
    void saveState() override;
    void addDartsInputModel(const DartsModelsContext::IDartsPointInput *model) override;
    const DartsModelsContext::IDartsPointInput *getDartsInputModelByIndex(const int &index) const override;
    QVector<const DartsModelsContext::IDartsPointInput *> dartsInputModels() const override;
    void removeDartsInputModelByIndex(const int &index) override;
    int indexOfDartsInputModel(const DartsModelsContext::IDartsPointInput *score) override;
    void replaceDartsInputModel(const int &index, const DartsModelsContext::IDartsPointInput *score) override;
    // Set service methods
    DartsPointJsonDbService* setDartsPointsExtractorService(JsonExtractor *dartsPointsExtractor);
    DartsPointJsonDbService* setDartsPointsJsonAssemblerService(JsonAssembler* dartsSingleAttemptPointInputAssembler);

private:
    // Services
    JsonExtractor* _dartsPointsExtractor;
    JsonAssembler* _dartsPointsJsonAssemblerService;
    const QString _fileName = "DartsPoints";

    QVector<const DartsModelsContext::IDartsPointInput*> _dartsPointModels;
};

#endif // DARTSPOINTDBSERVICE_H
