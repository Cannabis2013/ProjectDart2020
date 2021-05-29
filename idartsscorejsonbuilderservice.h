#ifndef IDARTSMULTIATTEMPTJSONSERVICE_H
#define IDARTSMULTIATTEMPTJSONSERVICE_H

#include "iunaryservice.h"
#include <qbytearray.h>
#include <qvector.h>
#include "idartsplayer.h"
#include "idartsmultiattemptindexes.h"

using namespace DartsScoreMultiAttemptContext;

template<typename TDartsInputInterface>
class IDartsScoreJsonBuilderService {
public:
    typedef TDartsInputInterface InputModelInterface;
    virtual QByteArray buildJsonByDartsScoreModels(const QVector<const InputModelInterface*>& inputModels) const = 0;
    virtual QByteArray assembleJsonAddScoreValues(const QUuid&,
                                                  const int&,
                                                  const int&,
                                                  const QUuid&,
                                                  const QUuid&,
                                                  const int&) const = 0;
    virtual QByteArray assembleJsonWinnerName(const QUuid&, const QUuid&) const = 0;
};

#endif // IDARTSMULTIATTEMPTJSONSERVICE_H
