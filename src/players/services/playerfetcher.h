#ifndef PLAYERFETCHER_H
#define PLAYERFETCHER_H

#include "iplayerfetcher.h"

class ServiceCollection;

class PlayerFetcher : public IPlayerFetcher {
public:
    PlayerFetcher(ServiceCollection* services);
    DartsPlayer &get(const int &index) override;
    DartsPlayer& get(const QString& name) override;
    DartsPlayer winner() const override;
    int indexOf(const QString& name) const override;
    QStringList names() const override;

private:
        ServiceCollection* _services;
};

#endif // PLAYERFETCHER_H
