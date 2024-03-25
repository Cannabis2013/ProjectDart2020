#ifndef DARTSSCORESDELTA_H
#define DARTSSCORESDELTA_H

#include "iscoresdelta.h"

class ServiceCollection;

class DartsScoresDelta : public IScoresDelta {
public:
        DartsScoresDelta(ServiceCollection* services);
        int delta() const override;

private:
        ServiceCollection* _services;
};

#endif // DARTSSCORESDELTA_H
