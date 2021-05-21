#ifndef IDARTSMULTIATTEMPTJSONSERVICE_H
#define IDARTSMULTIATTEMPTJSONSERVICE_H

#include "iunaryservice.h"
#include <qbytearray.h>
#include <qvector.h>
#include "idartsplayer.h"
#include "idartsmultiattemptindexes.h"

using namespace DartsScoreMultiAttemptContext;

template<typename TPlayerService>
class IDartsMultiAttemptJsonService {
public:
    virtual QByteArray assembleJsonDartsMultiAttemptScores(const TPlayerService*) const = 0;
    virtual int getScoreByJson(const QByteArray&) const = 0;
    virtual QByteArray assembleJsonTurnValues(const bool&, const bool&, const int&, const QString&, const QString&) const = 0;
    virtual QByteArray assembleJsonAddScoreValues(const QUuid&,
                                                  const int&,
                                                  const int&,
                                                  const QUuid&,
                                                  const QUuid&,
                                                  const int&) const = 0;
    virtual QByteArray assembleJsonWinnerName(const QUuid&, const QUuid&) const = 0;
};

#endif // IDARTSMULTIATTEMPTJSONSERVICE_H
