#ifndef DCINDEXCONTROLLER_H
#define DCINDEXCONTROLLER_H

#include <idcindexservice.h>
#include "idcmetainfo.h"

class DCIndexController : public IDCIndexService
{
public:
    DCIndexController(const DCBuilding::IDCMetaInfo *meta);
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
    virtual void setNumberOfAttempts(const int &) override;
private:
    int _turnIndex = 0;
    int _totalIndex  = 0;
    int _roundIndex = 1;
    int _setIndex = 0;
    int _attemptIndex = 0;
    int _playerCount;
    int _numberOfAttempts;
};
#endif // SCOREINDEXCONTROLLER_H
