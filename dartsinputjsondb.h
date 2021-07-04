#ifndef DARTSINPUTJSONDB_H
#define DARTSINPUTJSONDB_H

#include "idartsinputdb.h"
#include "jsonpersistence.h"
#include "icreateinputmodelsfromjson.h"
#include "icreatejsonfrominputs.h"

namespace DartsModelsContext {
    class DartsInputJsonDb :
            public IDartsInputDb,
            private JSONPersistence
    {
    public:
        DartsInputJsonDb(const QString &fileName);
        void add(const Model* model) override;
        const IPlayerInput *model(const int &index) const override;
        QVector<const Model *> models() const override;
        bool remove(const int &index) override;
        int indexOf(const Model* model) const override;
        void replace(const int &index, const Model* model) override;

    protected:
        void saveState() override;
        void fetchModels() override;
        ICreateInputModelsFromJson* _createInputModelsFromJson;
        ICreateJsonFromInputs *_createJsonFromInputModels;
    private:
        QString _fileName;
        QVector<const IPlayerInput*> _dartsScoreModels;
    };
}

#endif // DARTSSCOREDB_H
