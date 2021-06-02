#ifndef IPLAYERINPUTCOMPARISON_H
#define IPLAYERINPUTCOMPARISON_H

#include "idartsinput.h"

namespace DartsModelsContext {
    struct IPredicate{
        virtual bool operator()(const IModel<QUuid,QByteArray>*, const IModel<QUuid,QByteArray>*) const = 0;
    };
}


#endif // IPLAYERINPUTCOMPARISON_H
