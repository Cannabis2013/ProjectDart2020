#ifndef DARTSPOINTDBSERVICE_H
#define DARTSPOINTDBSERVICE_H

#include "abstractjsonpersistence.h"
#include "idartspointdb.h"
#include "idartspointinput.h"
#include <quuid.h>
#include "iunaryservice.h"
class DartsPointDbService :
        public IdartsPointDb,
        public AbstractJSONPersistence
{
public:
    typedef IUnaryService<const QJsonArray &, QVector<const IDartsPointInput *>> JsonExtractor;
    typedef IUnaryService<const QVector<const IDartsPointInput*>&,QJsonArray> JsonAssembler;
    static DartsPointDbService* createInstance(JsonExtractor* extractor, JsonAssembler* assembler);
    void fetchModels() override;
    void saveState() override;
    void addDartsInputModel(const IDartsPointInput *model) override;
    const IDartsPointInput *getDartsInputModelByIndex(const int &index) const override;
    QVector<const IDartsPointInput *> dartsInputModels() const override;
    void removeDartsInputModelByIndex(const int &index) override;
    int indexOfDartsInputModel(const IDartsPointInput *score) override;
    void replaceDartsInputModel(const int &index, const IDartsPointInput *score) override;
    // Set service methods
    DartsPointDbService* setDartsPointsExtractorService(JsonExtractor *dartsPointsExtractor);
    DartsPointDbService* setDartsPointsJsonAssemblerService(JsonAssembler* dartsSingleAttemptPointInputAssembler);

private:
    // Services
    JsonExtractor* _dartsPointsExtractor;
    JsonAssembler* _dartsPointsJsonAssemblerService;
    const QString _fileName = "DartsPoints";

    QVector<const IDartsPointInput*> _dartsPointModels;
};

#endif // DARTSPOINTDBSERVICE_H
