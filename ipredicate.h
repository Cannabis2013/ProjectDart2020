#ifndef IPLAYERINPUTCOMPARISON_H
#define IPLAYERINPUTCOMPARISON_H

#include "idartsinput.h"

namespace DartsModelsContext {
    struct IPredicate{
        virtual bool operator()(const IDartsInput*, const IDartsInput*) const = 0;
    };
}


#endif // IPLAYERINPUTCOMPARISON_H
