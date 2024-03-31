#ifndef PLAYERFETCHER_H
#define PLAYERFETCHER_H

#include "iplayerfetcher.h"

class ServiceCollection;

class PlayerFetcher : public IPlayerFetcher {
public:
        PlayerFetcher(ServiceCollection* services);
        DartsPlayer& one() override;
        DartsPlayer& one(const QString& name) override;
        DartsPlayer winner() const override;
        int indexOf(const QString& name) const override;

private:
        ServiceCollection* _services;
};

#endif // PLAYERFETCHER_H
