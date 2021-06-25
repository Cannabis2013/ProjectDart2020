#ifndef DARTSMETADATASERVICE_H
#define DARTSMETADATASERVICE_H

#include "idartsmetadata.h"

class DartsMetaDataService : public IDartsMetaData
{
public:

    static DartsMetaDataService *createInstance(const QUuid &tournamentId,const int &displayHint)
    {
        return new DartsMetaDataService(tournamentId, displayHint);
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
private:
    DartsMetaDataService(const QUuid &tournamentId,const int &displayHint)
    {
        _tournamentId = tournamentId;
        _displayHint = displayHint;
    }
    QUuid _tournamentId;
    int _displayHint;
    int _status;
};

#endif // DARTSMETADATASERVICE_H
