#include "dartsallowances.h"

using namespace std;

DartsAllowances::DartsAllowances()
{
}

void DartsAllowances::init(const QStringList& names)
{
        _allowances.clear();
        for (const auto& name : names)
                _allowances.insert(name, false);
}

bool DartsAllowances::isAllowed(const QString& name)
{
        return _allowances.value(name);
}

bool DartsAllowances::updateAllowance(const QString& name, const bool& allowed)
{
        if (_allowances.contains(name))
                _allowances.insert(name, allowed);
        return allowed;
}
