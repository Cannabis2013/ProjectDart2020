#ifndef IDARTSPOINTDB_H
#define IDARTSPOINTDB_H

#include <qvector.h>
#include <idartspointinput.h>
#include "imodelsdbcontext.h"

namespace DartsModelsContext
{
    class IDartsPointDb : public IModelsDbContext<IDartsInput,QUuid>
    {
    public:
        virtual void addModel(const IDartsInput* model) override = 0;
        virtual const IDartsInput* getModelByIndex(const int& index) const = 0;
        virtual QVector<const IDartsInput*> models() const override = 0;
        virtual bool removeModelByIndex(const int&) override = 0;
        virtual bool removeModelById(const QUuid &) override = 0;
        virtual int indexOfModel(const IDartsInput*) override = 0;
        virtual void replaceModel(const int&, const IDartsInput*) override = 0;
        virtual const IDartsInput *modelByIndex(const int &) const override = 0;
        virtual const IDartsInput *modelById(const QUuid &) const override = 0;
    };
}


#endif // IDARTSPOINTDB_H
