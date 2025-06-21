#ifndef IPLAYERREPORT_H
#define IPLAYERREPORT_H

class QString;
class QByteArray;

class IPlayerReport {
public:
    virtual QByteArray all() const = 0;
    virtual QString current() const = 0;
    virtual bool isWinnerFound() const = 0;
    virtual QByteArray winnerInfo() const = 0;
    virtual QByteArray report() const = 0;
};

#endif // IPLAYERREPORT_H
