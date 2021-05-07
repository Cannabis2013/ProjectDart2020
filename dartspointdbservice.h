#ifndef DARTSPOINTDBSERVICE_H
#define DARTSPOINTDBSERVICE_H

#include "abstractjsonpersistence.h"
#include "idartspointdb.h"
#include "idartspointinput.h"
#include <quuid.h>
#include "iunaryservice.h"
class DartsPointDbService :
        public IdartsPointDb<IDartsPointInput<QUuid>>,
        public AbstractJSONPersistence
{
public:
    static DartsPointDbService* createInstance();
    void fetchModels() override;
    void saveState() override;
    void addDartsInputModel(const IDartsPointInput<QUuid> *model) override;
    const IDartsPointInput<QUuid> *getDartsInputModelByIndex(const int &index) const override;
    QVector<const IDartsPointInput<QUuid> *> dartsInputModels() const override;
    void removeDartsInputModelByIndex(const int &index) override;
    int indexOfDartsInputModel(const IDartsPointInput<QUuid> *score) override;
    void replaceDartsInputModel(const int &index, const IDartsPointInput<QUuid> *score) override;
    // Set service methods
    DartsPointDbService* setDartsPointsExtractorService(IUnaryService<const QJsonArray &, QVector<const IDartsPointInput<QUuid> *> > *dartsPointsExtractor);
    DartsPointDbService* setDartsPointsJsonAssemblerService(IUnaryService<const QVector<const IDartsPointInput<QUuid>*>&,
                                                                  QJsonArray>* dartsSingleAttemptPointInputAssembler);

private:
    // Services
    IUnaryService<const QJsonArray&,QVector<const IDartsPointInput<QUuid>*>>* _dartsPointsExtractor;
    IUnaryService<const QVector<const IDartsPointInput<QUuid>*>&,QJsonArray>* _dartsPointsJsonAssemblerService;
    const QString _fileName = "DartsPoints";

    QVector<const IDartsPointInput<QUuid>*> _dartsPointModels;
};

#endif // DARTSPOINTDBSERVICE_H
