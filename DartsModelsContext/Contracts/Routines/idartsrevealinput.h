#ifndef IDARTSREVEALINPUT_H
#define IDARTSREVEALINPUT_H

#include <DartsModelsContext/Contracts/dartsmodelsservices.h>
#include <quuid.h>

template<typename TModel> class IDartsRevealInput
{
public:
    typedef TModel Model;
    virtual bool display(QUuid tournamentID, QString name, const QByteArray &indexAsByteArray, DartsModelsServices *services) = 0;
};

#endif // IDARTSREVEALINPUT_H
