#ifndef DARTSSCORESFETCH_H
#define DARTSSCORESFETCH_H

#include "idartsscoresfetch.h"

class ServiceCollection;

class DartsScoresFetch : public IDartsScoresFetch {
public:
        DartsScoresFetch(ServiceCollection* services);

        Score score() override;
        Score score(const QString& name) override;

private:
        ServiceCollection* _services;
};

#endif // DARTSSCORESFETCH_H