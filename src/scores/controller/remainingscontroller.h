#ifndef DARTSSCORESREPORT_H
#define DARTSSCORESREPORT_H

#include "iremainings.h"
#include <QObject>

class IDartsFinishes;
class IDartsIndexes;
class ServiceCollection;
class IDartsRemainings;

class RemainingsController : public QObject, public IRemainings {
    Q_OBJECT
  public:
    RemainingsController(ServiceCollection* services);
    Q_INVOKABLE QList<int> all() const override;
    Q_INVOKABLE int remaining(const QString &playerName) const override;
    Q_INVOKABLE int current() const override;

  private:
    ServiceCollection* _services;
};

#endif // DARTSSCORESREPORT_H
