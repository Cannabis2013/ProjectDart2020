#ifndef IREMOVEINPUTFROMDB_H
#define IREMOVEINPUTFROMDB_H
class QString;
class IRemoveInputFromDb
{
public:
    virtual bool remove(const QString &name) = 0;
};

#endif // IREMOVEINPUTFROMDB_H
