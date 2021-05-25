#ifndef IMODELSDBCONTEXT_H
#define IMODELSDBCONTEXT_H

#include <qvector.h>

namespace DartsModelsContext {
    template<typename TModel, typename TUuid>
    class IModelsDbContext
    {
    public:
        virtual void addModel(const TModel*) = 0;
        virtual const TModel* modelByIndex(const int&) const = 0;
        virtual const TModel* modelById(const TUuid&) const = 0;
        virtual QVector<const TModel*> models() const = 0;
        virtual bool removeModelByIndex(const int&) = 0;
        virtual bool removeModelById(const TUuid&) = 0;
        virtual int indexOfModel(const TModel*) = 0;
        virtual void replaceModel(const int&, const TModel*) = 0;
    };
}

#endif // IMODELSDBCONTEXT_H
