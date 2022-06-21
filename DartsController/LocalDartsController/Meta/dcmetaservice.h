#ifndef DCMETASERVICE_H
#define DCMETASERVICE_H

#include <quuid.h>
#include <DartsController/Contracts/Meta/idcmetamanager.h>
#include <DartsController/Contracts/Models/dcmeta.h>

class DCMetaService : public IDCMetaManager<DCMeta>
{
public:
    void setMeta(const QUuid &id, const int &initialRemaining) override
    {
        _meta.tournamentID = id;
        _meta.initRemScore = initialRemaining;
    }
    void setMeta(const DCMeta &meta) override {_meta = meta;}
    DCMeta &meta() override {return _meta;}
    int initRemScore() const override {return _meta.initRemScore;}
    int status() const override {return _meta.status;}
    void setStatus(const int &status) override {_meta.status = status;}
    QUuid tournamentID() const override {return _meta.tournamentID;}
    virtual QString winnerName() const override {return _meta.winnerName;}
private:
    DCMeta _meta;
};
#endif // DCTOURNAMENTID_H
