#ifndef DMCINPUTJSONDB_H
#define DMCINPUTJSONDB_H

#include "ModelsContext/MCDbSLAs/imodelsdbcontext.h"
#include "modelsdbjsonslas.h"
#include "modelsdbioservices.h"

namespace DartsDbContext {
    class DMCInputJsonDb :
            public IModelsDbContext,
            protected ModelsDbJsonSLAs,
            protected ModelsDbIOSLAs
    {
    public:
        void add(const IModel<QUuid>* model) override;
        const IModel<QUuid> *model(const int &index) const override;
        QVector<const IModel<QUuid>*> models() const override;
        bool remove(const int &index) override;
        int indexOf(const IModel<QUuid>* model) const override;
        void replace(const int &index, const IModel<QUuid>* model) override;
    protected:
        void saveState() override;
        void fetchModels() override;
    private:
        QString _fileName;
        QVector<const IModel<QUuid>*> _dartsScoreModels;
    };
}

#endif // DARTSSCOREDB_H
