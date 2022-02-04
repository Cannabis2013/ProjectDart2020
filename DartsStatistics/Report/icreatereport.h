#ifndef ICREATEREPORT_H
#define ICREATEREPORT_H
struct PlayerStat;
class QByteArray;
class ICreateReport
{
public:
    typedef QByteArray ByteArray;
    virtual ByteArray create(const PlayerStat &player) const = 0;
};

#endif // ICREATEREPORT_H
