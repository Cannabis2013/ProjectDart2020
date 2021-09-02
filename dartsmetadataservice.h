#ifndef DARTSMETADATASERVICE_H
#define DARTSMETADATASERVICE_H

#include "idartsmetadata.h"

class DartsMetaDataService : public IDartsMetaData
{
public:
    DartsMetaDataService(const QUuid &tournamentId,const int &displayHint, const int &initialScore)
    {
        _tournamentId = tournamentId;
        _displayHint = displayHint;
        _initialScore = initialScore;
    }
    virtual int status() const override
    {
        return _status;
    }
    virtual void setStatus(const int &status) override
    {
        _status = status;
    }
    virtual QUuid tournamentId() const override
    {
        return _tournamentId;
    }
    virtual int displayHint() const override
    {
        return _displayHint;
    }
    virtual int initialScore() const override
    {
        return _initialScore;
    }
private:
    QUuid _tournamentId;
    int _displayHint;
    int _status;
    int _initialScore;
};
#endif // DARTSMETADATASERVICE_H
