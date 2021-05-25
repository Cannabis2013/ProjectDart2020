#ifndef IPLAYERINPUTCOMPARISON_H
#define IPLAYERINPUTCOMPARISON_H

#include "idartsinput.h"

namespace DartsModelsContext {
    struct Predicate{
        virtual bool operator()(const IDartsInput*, const IDartsInput*) const = 0;
    };
}


#endif // IPLAYERINPUTCOMPARISON_H
