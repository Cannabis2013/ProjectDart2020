#ifndef IDARTSMETADATA_H
#define IDARTSMETADATA_H

#include <quuid.h>

class IDartsMetaData
{
public:
    virtual int status() const = 0;
    virtual void setStatus(const int &status) = 0;
    virtual QUuid tournamentId() const = 0;
    virtual int displayHint() const = 0;
    virtual int inputHint() const = 0;
    virtual int initialScore() const = 0;
};

#endif // IDARTSMETADATASERVICE_H
