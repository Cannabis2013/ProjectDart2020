#ifndef DCMETACONTEXT_H
#define DCMETACONTEXT_H
#include "DartsController/DCMetaSLAs/idcmetacontext.h"
#include <quuid.h>
class DCMetaContext : public IDCMetaContext
{
public:
    void set(const QUuid &id, const int &initialRemaining) override
    {
        _meta.tournamentId = id;
        _meta.initRemScore = initialRemaining;
    }
    void set(const int &status) override {_meta.status = status;}
    void set(const DCMeta &meta) override {_meta = meta;}
    DCMeta &get() override {return _meta;}
    int initRemScore() const override {return _meta.initRemScore;}
    int status() const override {return _meta.status;}
    QUuid tournamentId() const override {return _meta.tournamentId;}
    virtual QString winnerName() const override {return _meta.winnerName;}
private:
    DCMeta _meta;
};
#endif // DCTOURNAMENTID_H
