#ifndef DARTSALLOWANCES_H
#define DARTSALLOWANCES_H

#include "iplayerallowances.h"

#include <QHash>
#include <QList>

class DartsAllowances : public IPlayerAllowances {
public:
        DartsAllowances();
        virtual void init(const QStringList& names) override;
        virtual bool isAllowed(const QString& name) override;
        virtual bool updateAllowance(const QString& name, const bool& allowed) override;

private:
        QHash<QString, bool> _allowances;
};

#endif // DARTSALLOWANCES_H
