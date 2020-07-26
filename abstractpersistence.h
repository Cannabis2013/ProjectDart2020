#ifndef ABSTRACTPERSISTENCE_H
#define ABSTRACTPERSISTENCE_H

#include <qsettings.h>
#include <qjsonobject.h>

class AbstractPersistence
{
public:
    virtual void read() = 0;
    virtual void write() = 0;
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





