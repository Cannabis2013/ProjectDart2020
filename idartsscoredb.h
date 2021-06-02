#ifndef IDARTSSCOREDB_H
#define IDARTSSCOREDB_H

#include <qvector.h>
#include "idartsscoreinput.h"
#include "imodelsdbcontext.h"
#include "ipersistence.h"

namespace DartsModelsContext {
    class IDartsScoreDb :
            public IModelsDbContext<IPlayerInput,QUuid>,
            public IPersistence
    {
    public:
        virtual void addModel(const Model* model) override = 0;
        virtual const Model* modelByIndex(const int&) const override = 0;
        virtual const Model* modelById(const QUuid&) const override = 0;
        virtual QVector<const Model*> models() const override = 0;
        virtual bool removeModelByIndex(const int&) override = 0;
        virtual bool removeModelById(const QUuid&) override = 0;
        virtual int indexOfModel(const Model*) override = 0;
        virtual void replaceModel(const int&, const Model*) override = 0;
    };
}


#endif // IDARTSSCOREDB_H
