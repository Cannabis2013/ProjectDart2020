#ifndef IDARTSPLAYERBUILDER_H
#define IDARTSPLAYERBUILDER_H

#include <qvector.h>

namespace DartsPointControllerContext {
    template<typename TModelsInterface, typename TString, typename TUuid,typename TJsonFormat>
    class IDartsPlayerModelBuilderService
    {
    public:
        typedef TModelsInterface ModelsInterface;
        typedef TString StringFormat;
        typedef TUuid IdFormat;
        typedef TJsonFormat JsonFormat;
        virtual QVector<const ModelsInterface*> createPlayerModelsByJson(const JsonFormat& json) const = 0;
        virtual const ModelsInterface* createPlayerModelByValues(const IdFormat &id,const StringFormat &name) const = 0;
    };
}

#endif // IDARTSPLAYERBUILDER_H
