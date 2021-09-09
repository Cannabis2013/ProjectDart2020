#ifndef DCMETAINFO_H
#define DCMETAINFO_H
#include "idartsmetadata.h"

#include <idcmetainfo.h>
class DCMetaInfo : public IDartsMetaData
{
public:
    DCMetaInfo(const DartsBuilderContext::IDCMetaInfo *details)
    {
        _inputHint = details->inputHint();
        _tournamentId = details->tournamentId();
        _displayHint =  details->displayHint();
        _initialScore = details->keyPoint();
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
    virtual int inputHint() const override
    {
        return _inputHint;
    }
private:
    QUuid _tournamentId;
    int _displayHint;
    int _inputHint;
    int _status;
    int _initialScore;
};
#endif // DARTSMETADATASERVICE_H
