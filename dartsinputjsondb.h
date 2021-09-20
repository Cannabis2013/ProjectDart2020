#ifndef DARTSINPUTJSONDB_H
#define DARTSINPUTJSONDB_H

#include "ModelsContext/imodelsdbcontext.h"
#include "modelsdbjsonservices.h"
#include "modelsdbioservices.h"

namespace DartsDbContext {
    class DartsInputJsonDb :
            public IModelsDbContext,
            protected ModelsDbJsonServices,
            protected ModelsDbIOServices
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
