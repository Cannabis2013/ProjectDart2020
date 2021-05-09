#ifndef DARTSSCOREDB_H
#define DARTSSCOREDB_H

#include "idartsscoredb.h"
#include "abstractjsonpersistence.h"
#include "iunaryservice.h"

class DartsScoreJsonDb :
        public IDartsScoreDb,
        private AbstractJSONPersistence
{
public:
    typedef IUnaryService<const QJsonObject &, QVector<const IDartsScoreInput *>> JsonExtractor;
    typedef IUnaryService<const QVector<const IDartsScoreInput*>&,QJsonObject> JsonAssembler;
    static DartsScoreJsonDb* createInstance(JsonExtractor* extractor, JsonAssembler* assembler);
    void addDartsInputModel(const IDartsScoreInput *model) override;
    const IDartsScoreInput *getDartsInputModelByIndex(const int &index) const override;
    QVector<const IDartsScoreInput *> dartsInputModels() const override;
    void removeDartsInputModelByIndex(const int &index) override;
    int indexOfDartsInputModel(const IDartsScoreInput *model) override;
    void replaceDartsInputModel(const int &index, const IDartsScoreInput *model) override;
    DartsScoreJsonDb* setDartsScoresExtractorService(JsonExtractor *dartsScoresExtractor);
    DartsScoreJsonDb* setDartsScoresJsonAssemblerService(JsonAssembler *dartsScoresJsonAssemblerService);

private:
    void fetchModels() override;
    void saveState() override;

    JsonExtractor* _jsonExtractorService;
    JsonAssembler* _jsonAssemblerService;
    const QString _fileName = "DartsPoints";

    QVector<const IDartsScoreInput*> _dartsScoreModels;
};

#endif // DARTSSCOREDB_H
