#ifndef IDARTSMULTIATTEMPTJSONSERVICE_H
#define IDARTSMULTIATTEMPTJSONSERVICE_H

#include "iunaryservice.h"
#include <qbytearray.h>
#include <qvector.h>
#include "idartsplayer.h"
#include "idartsmultiattemptindexes.h"

using namespace DartsScoreMultiAttemptContext;

template<typename TModelInterface, typename TDartsIndexes, typename TJsonFormat, typename TString>
class IDartsScoreJsonBuilderService {
public:
    typedef TModelInterface ModelInterface;
    typedef TDartsIndexes DartsIndexes ;
    typedef TString StringFormat;
    typedef TJsonFormat JsonFormat;
    virtual JsonFormat buildJsonByDartsScoreModels(const QVector<const ModelInterface*>& inputModels) const = 0;
    virtual JsonFormat buildJsonAddScoreValues(const DartsIndexes* indexes, const ModelInterface* dartsModel) const = 0;
    virtual JsonFormat assembleJsonWinnerName(const QUuid&, const QUuid&) const = 0;
};

#endif // IDARTSMULTIATTEMPTJSONSERVICE_H
