#ifndef IDARTSMULTIATTEMPTJSONSERVICE_H
#define IDARTSMULTIATTEMPTJSONSERVICE_H

#include "iunaryservice.h"
#include <qbytearray.h>
#include <qvector.h>
#include "idartsplayer.h"
#include "idartsscorecontrollerindexes.h"

using namespace DartsScoreControllerContext;

template<typename TModelInterface, typename TDartsIndexes, typename TJsonFormat, typename TString>
class IDartsScoreJsonBuilderService {
public:
    typedef TModelInterface ModelInterface;
    typedef TDartsIndexes DartsIndexes ;
    typedef TString StringFormat;
    typedef TJsonFormat JsonFormat;
    virtual JsonFormat createJsonByDartsScoreModels(const QVector<const ModelInterface*>& inputModels) const = 0;
    virtual JsonFormat createJsonByDartsScore(const ModelInterface* dartsModel) const = 0;
    virtual JsonFormat createJsonByIds(const QUuid&, const QUuid&) const = 0;
};

#endif // IDARTSMULTIATTEMPTJSONSERVICE_H
