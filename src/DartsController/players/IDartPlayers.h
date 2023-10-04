#ifndef IDARTPLAYERS_H
#define IDARTPLAYERS_H

#include <qstring.h>

class IDartPlayers
{
public:
        virtual void initPlayers(const QStringList &names) = 0;
        virtual void initPlayers() = 0;
        virtual int playersCount() = 0;
        virtual QString name(int index) const = 0;
        virtual QStringList names() const = 0;
};

#endif // IDARTPLAYERS_H
