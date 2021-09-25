#ifndef DSCINDEXCONTROLLER_H
#define DSCINDEXCONTROLLER_H

#include "DartsController/DCIndexSLAs/idcindexservice.h"
#include "DartsControllerBuilder/DCBMetaSLAs/idcmetainfo.h"

class DSCIndexController : public IDCIndexService
{
public:
    virtual int turnIndex() const override;
    virtual void setTurnIndex(const int &index) override;
    virtual int totalIndex() const override;
    virtual void setTotalIndex(const int &index) override;
    virtual int roundIndex() const override;
    virtual void setRoundIndex(const int &index) override;
    virtual int setIndex() const override;
    virtual void setSetIndex(const int &index) override;
    virtual int attemptIndex() const override;
    virtual void setAttemptIndex(const int &index) override;
    virtual void syncIndex() override;
    virtual int numberOfAttempts() const override;
private:
    int _turnIndex = 0;
    int _totalIndex  = 0;
    int _roundIndex = 1;
    int _setIndex = 0;
    int _attemptIndex = 0;
    const int _numberOfAttempts = 1;
};

#endif // DSCINDEXCONTROLLER_H
