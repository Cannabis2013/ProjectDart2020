#ifndef IDARTSADDINPUTTODB_H
#define IDARTSADDINPUTTODB_H
class QUuid;
class QByteArray;
class IDartsAddInputToDb
{
public:
    typedef QByteArray ByteArray;
    virtual void add(const ByteArray &byteArray, const QUuid &tournamentID) = 0;
};

#endif // IDARTSCREATEINPUT_H
