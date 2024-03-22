#ifndef IPLAYERFETCHER_H
#define IPLAYERFETCHER_H

class QString;
class DartsPlayer;

class IPlayerFetcher {
public:
        virtual DartsPlayer& one() = 0;
        virtual DartsPlayer& one(const QString& name) = 0;
        virtual DartsPlayer winner() const = 0;
};

#endif // IPLAYERFETCHER_H
