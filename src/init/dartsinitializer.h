#ifndef CONTROLLERINITIALIZER_H
#define CONTROLLERINITIALIZER_H

#include "src/init/iserviceinitializer.h"
#include <QObject>
#include <QString>

class DartsInitializer : public QObject, public IServiceInitializer {
  public:
    DartsInitializer(ServiceCollection* services);

    Q_INVOKABLE void init(const QByteArray& json) override;
    Q_INVOKABLE void initFromStorage() override;
    Q_INVOKABLE void reset() override;
    Q_INVOKABLE void saveState() override;

  private:
    Q_OBJECT
    ServiceCollection* const _services;
};

#endif // CONTROLLERINITIALIZER_H
