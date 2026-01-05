#ifndef PLAYERCONTROLLER_H
#define PLAYERCONTROLLER_H

#include "IPlayers.h"

#include <QObject>

class ServiceCollection;
class PlayerController : public QObject, public IPlayers
{
    Q_OBJECT
  public:
    PlayerController(ServiceCollection* services);

    Q_INVOKABLE QStringList all() const override;
    Q_INVOKABLE QString current() const override;
    Q_INVOKABLE int playerIndex(const QString& name) const override;

  private:
    ServiceCollection* _services;
};

#endif // PLAYERCONTROLLER_H
