#ifndef IDARTSPOINTDB_H
#define IDARTSPOINTDB_H

#include <qvector.h>
#include <idartspointinput.h>
#include "imodelsdbcontext.h"
#include "ipersistence.h"

namespace DartsModelsContext
{
    class IDartsPointDb : public IModelsDbContext<IPlayerInput>,
            public IPersistence
    {
    public:
        // IModelsDbContext interface
        typedef QVector<const Model*> PlayerInputs;
        virtual void addModel(const Model* model) override = 0;
        virtual const Model* getModelByIndex(const int& index) const = 0;
        virtual QVector<const Model*> models() const override = 0;
        virtual bool removeModelByIndex(const int&) override = 0;
        virtual int indexOfModel(const Model*) override = 0;
        virtual void replaceModel(const int&, const Model*) override = 0;
        virtual const Model *modelByIndex(const int &) const override = 0;
        // IPersistence interface
        virtual void fetchModels() override = 0;
        virtual void saveState() override = 0;
    };
}


#endif // IDARTSPOINTDB_H
