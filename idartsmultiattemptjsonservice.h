#ifndef IDARTSMULTIATTEMPTJSONSERVICE_H
#define IDARTSMULTIATTEMPTJSONSERVICE_H

#include "iunaryservice.h"
#include <qbytearray.h>
#include <qvector.h>
#include <iplayerscoreservice.h>
#include "idartsplayer.h"
#include "idartsmultiattemptindexes.h"

using namespace DartsScoreMultiAttemptContext;

class IDartsMultiAttemptJsonService {
public:
    virtual QByteArray assembleJsonDartsMultiAttemptScores(const IPlayerScoreService*) const = 0;
    virtual int getScoretByJson(const QByteArray&) const = 0;
    virtual QByteArray assembleJsonFromParameters(const QString&, const int&) const = 0;
    virtual QByteArray assembleJsonDartsScore(const QString&, const int&) const = 0;
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
