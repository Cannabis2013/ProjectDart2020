#ifndef DCMETACONTEXT_H
#define DCMETACONTEXT_H
#include "DCMetaSLAs/idcmetacontext.h"
#include <quuid.h>
#include "Models/dcmeta.h"
class DCMetaContext : public IDCMetaContext<DCMeta>
{
public:
    void setMeta(const QUuid &id, const int &initialRemaining) override
    {
        _meta.tournamentId = id;
        _meta.initRemScore = initialRemaining;
    }
    void setMeta(const int &status) override {_meta.status = status;}
    void setMeta(const DCMeta &meta) override {_meta = meta;}
    DCMeta &meta() override {return _meta;}
    int initRemScore() const override {return _meta.initRemScore;}
    int status() const override {return _meta.status;}
    QUuid tournamentId() const override {return _meta.tournamentId;}
    virtual QString winnerName() const override {return _meta.winnerName;}
private:
    DCMeta _meta;
};
#endif // DCTOURNAMENTID_H
