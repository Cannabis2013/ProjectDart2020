#ifndef IPLAYERREPORT_H
#define IPLAYERREPORT_H

class QByteArray;

class IPlayerReport {
public:
        virtual QByteArray report() const = 0;
        virtual QByteArray playerOne() const = 0;
        virtual QByteArray playerTwo() const = 0;
};

#endif // IPLAYERREPORT_H
