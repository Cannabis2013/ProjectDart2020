#ifndef IDCMETACONTEXT_H
#define IDCMETACONTEXT_H
#include <DartsController/DCMetaServices/dcmeta.h>
class IDCMetaContext
{
public:
    enum ControllerState {
        Initialized,
        Running,
        WinnerDeclared,
        AwaitsInput
    };
    virtual void set(const QUuid &id, const int &initialRemaining) = 0;
    virtual void set(const int &status) = 0;
    virtual void set(const DCMeta &meta) = 0;
    virtual int initRemScore() const = 0;
    virtual int status() const = 0;
    virtual QUuid tournamentId() const = 0;
    virtual QString winnerName() const = 0;
    virtual DCMeta &get() = 0;
};
#endif // IDCMETACONTEXT_H
