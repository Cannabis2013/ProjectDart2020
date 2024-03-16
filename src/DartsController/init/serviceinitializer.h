#ifndef CONTROLLERINITIALIZER_H
#define CONTROLLERINITIALIZER_H

#include "src/DartsController/init/iserviceinitializer.h"
#include <QObject>
#include <QString>

class ServiceInitializer : public QObject, public IServiceInitializer {
        Q_OBJECT
public:
        ServiceInitializer(ServiceCollection* services);

        Q_INVOKABLE void init(const QByteArray& json) override;
        Q_INVOKABLE void initFromStorage() override;
        Q_INVOKABLE void reset() override;
        Q_INVOKABLE void saveState() override;

private:
        ServiceCollection* const _services;
};

#endif // CONTROLLERINITIALIZER_H
