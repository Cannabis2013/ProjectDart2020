#ifndef IDATAMODELBUILDER_H
#define IDATAMODELBUILDER_H

#include <qvector.h>

template<typename TModelInterface, typename TJsonFormat>
class IDartsTournamentBuilder
{
public:
    typedef TModelInterface ModelInterface;
    typedef TJsonFormat  JsonFormat;
    virtual const ModelInterface* buildDartsTournamentModelByJson(const JsonFormat& json) = 0;
};

#endif // IDATAMODELBUILDER_H
