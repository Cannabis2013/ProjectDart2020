#ifndef IMODELSDBCONTEXT_H
#define IMODELSDBCONTEXT_H

#include <qvector.h>

namespace DartsModelsContext {
    template<typename TModel>
    class IModelsDbContext
    {
    public:
        typedef TModel Model;
        virtual void addModel(const TModel*) = 0;
        virtual const Model* modelByIndex(const int&) const = 0;
        virtual QVector<const Model*> models() const = 0;
        virtual bool removeModelByIndex(const int&) = 0;
        virtual int indexOfModel(const Model*) = 0;
        virtual void replaceModel(const int&, const Model*) = 0;
    };
}

#endif // IMODELSDBCONTEXT_H
