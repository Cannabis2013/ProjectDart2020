#ifndef IDARTSPLAYERBUILDER_H
#define IDARTSPLAYERBUILDER_H

#include <qvector.h>

namespace DartsPointControllerContext {
    template<typename TModelsInterface, typename TJsonFormat>
    class IDartsPlayerModelBuilderService
    {
    public:
        typedef TModelsInterface ModelsInterface;
        typedef TJsonFormat JsonFormat;
        virtual QVector<const ModelsInterface*> buildPlayerModelsByJson(const JsonFormat& json) const = 0;
    };
}

#endif // IDARTSPLAYERBUILDER_H
