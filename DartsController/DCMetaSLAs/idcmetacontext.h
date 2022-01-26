#ifndef IDCMETACONTEXT_H
#define IDCMETACONTEXT_H
class QUuid;
class QString;
struct DCMeta;
template<typename TMeta>
class IDCMetaContext
{
public:
    typedef TMeta Meta;
    enum ControllerState {
        Initialized,
        Running,
        WinnerDeclared,
        AwaitsInput
    };
    virtual void setMeta(const QUuid &id, const int &initialRemaining) = 0;
    virtual void setMeta(const int &status) = 0;
    virtual void setMeta(const DCMeta &meta) = 0;
    virtual int initRemScore() const = 0;
    virtual int status() const = 0;
    virtual QUuid tournamentId() const = 0;
    virtual QString winnerName() const = 0;
    virtual Meta &meta() = 0;
};
#endif // IDCMETACONTEXT_H
