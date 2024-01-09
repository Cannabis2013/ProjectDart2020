#ifndef IPLAYERALLOWANCES_H
#define IPLAYERALLOWANCES_H

#include <QString>

class IPlayerAllowances {
public:
        virtual void init(const QStringList& names) = 0;
        virtual bool isAllowed(const QString& name) = 0;
        virtual bool updateAllowance(const QString& name, const bool& allowed) = 0;
};

#endif // IPLAYERALLOWANCES_H
