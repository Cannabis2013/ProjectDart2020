#ifndef IPLAYERINPUTCOMPARISON_H
#define IPLAYERINPUTCOMPARISON_H

#include "DartsModelsContext/DMCInputSLAs/idartsinput.h"

template<typename TModelInterface>
struct IModelPredicate{
    typedef TModelInterface ModelInterface;
    virtual bool operator()(const ModelInterface*, const ModelInterface*) const = 0;
};

#endif // IPLAYERINPUTCOMPARISON_H
