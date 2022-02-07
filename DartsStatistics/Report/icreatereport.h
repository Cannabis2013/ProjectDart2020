#ifndef ICREATEREPORT_H
#define ICREATEREPORT_H
class QString;
class QByteArray;
class ICreateReport
{
public:
    typedef QByteArray ByteArray;
    virtual ByteArray create(const QString &name) const = 0;
};

#endif // ICREATEREPORT_H
