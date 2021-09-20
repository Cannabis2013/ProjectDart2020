#ifndef DCMETAINFO_H
#define DCMETAINFO_H
#include "idcinitialscore.h"

#include <idcmetainfo.h>
class DCMetaInfo : public IDCInitialScore
{
public:
    DCMetaInfo(const int &value)
    {
        _initialScore = value;
    }
    virtual int score() const override
    {
        return _initialScore;
    }
private:
    int _initialScore;
};
#endif // DARTSMETADATASERVICE_H
