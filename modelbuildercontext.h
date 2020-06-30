#ifndef MODELBUILDERCONTEXT_H
#define MODELBUILDERCONTEXT_H

#include <qstring.h>
#include <quuid.h>
#include <qlist.h>

namespace DataContext {
    class TournamentParameters;
    struct RoundParameters;
    struct SetParameters;
    struct PointParameters;
    struct ModelOptions;
}

template<class TString, class TUuid>
class ITournamentParameters
{
public:
    virtual TString title() const = 0;
    virtual int maximumPlayers() const = 0;
    virtual int numberOfLegs() const = 0;
    virtual int gameMode() const = 0;
    virtual int keyPoint() const = 0;
    virtual int status() const = 0;
};

struct TournamentParameters
{
    QString title;
    int maxPlayers;
    int numberOfLegs;
    int gameMode;
    int keyPoint;
    int status;
    QUuid winner;
    QUuid id;
    QList<QUuid> playerIdentities;
};

struct RoundParameters
{
    int roundIndex;
    QUuid tournamentId;
    QUuid id;
};

struct SetParameters
{
    int index;
    QUuid roundId;
    QUuid id;
};

struct PointParameters
{
    int pointValue;
    int legIndex;
    QUuid playerId;
    QUuid setId;
    QUuid id;
};

struct ModelOptions
{
    bool generateUniqueId = true;
    bool customUuid = false;
};

#endif // MODELBUILDERCONTEXT_H
