#ifndef IDARTSADDINPUTTODB_H
#define IDARTSADDINPUTTODB_H

class QUuid;
class QByteArray;
class DartsModelsServices;

class IDartsAddInputToDb
{
public:
    typedef QByteArray ByteArray;
    virtual bool add(const ByteArray &inputAsByteArray,
                     const ByteArray &indexAsByteArray,
                     const QUuid &tournamentID,
                     DartsModelsServices *services) = 0;
};

#endif // IDARTSCREATEINPUT_H
