#ifndef IDPCINDEXSERVICE_H
#define IDPCINDEXSERVICE_H

#include <idcindexservice.h>

class IDPCIndexService : public IDCIndexService
{
public:
    virtual int attemptIndex() const = 0;
    virtual void setAttempt(const int&) = 0;
    virtual int numberOfAttempts() const = 0;
    virtual void setNumberOfAttempts(const int&) = 0;
};

#endif // IDPCINDEXSERVICE_H
