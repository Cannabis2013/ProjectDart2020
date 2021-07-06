#ifndef IPLAYERINPUTCOMPARISON_H
#define IPLAYERINPUTCOMPARISON_H

#include "idartsinput.h"

template<typename TModelInterface>
struct IPredicate{
    typedef TModelInterface ModelInterface;
    virtual bool operator()(const ModelInterface*, const ModelInterface*) const = 0;
};

#endif // IPLAYERINPUTCOMPARISON_H
