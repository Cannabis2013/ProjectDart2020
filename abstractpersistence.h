#ifndef ABSTRACTPERSISTENCE_H
#define ABSTRACTPERSISTENCE_H

#include <qsettings.h>
#include "persistenceinterface.h"


class AbstractPersistence : public PersistenceInterface
{
public:

protected:
    AbstractPersistence(const QString &orgName, const QString &appName)
    {
        _settings = new QSettings(orgName,appName);
    }

    QSettings *settings() const
    {
        return _settings;
    }

private:
    QSettings *_settings = nullptr;
};

#endif // ABSTRACTPERSISTENCE_H





