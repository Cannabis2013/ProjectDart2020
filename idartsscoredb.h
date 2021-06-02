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
        virtual void addModel(const IPlayerInput* model) override = 0;
        virtual const IDartsScoreInput* modelByIndex(const int&) const override = 0;
        virtual const IDartsScoreInput* modelById(const QUuid&) const override = 0;
        virtual QVector<const IPlayerInput*> models() const override = 0;
        virtual bool removeModelByIndex(const int&) override = 0;
        virtual bool removeModelById(const QUuid&) override = 0;
        virtual int indexOfModel(const IPlayerInput*) override = 0;
        virtual void replaceModel(const int&, const IPlayerInput*) override = 0;
    };
}


#endif // IDARTSSCOREDB_H
