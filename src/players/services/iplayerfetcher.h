#ifndef IPLAYERFETCHER_H
#define IPLAYERFETCHER_H

#include <QStringList>

class QString;
class DartsPlayer;

class IPlayerFetcher {
public:
        virtual int indexOf(const QString& name) const = 0;
        virtual DartsPlayer &get(const int &index) = 0;
        virtual DartsPlayer& get(const QString& name) = 0;
        virtual DartsPlayer winner() const = 0;
        virtual QStringList names() const = 0;
};

#endif // IPLAYERFETCHER_H
