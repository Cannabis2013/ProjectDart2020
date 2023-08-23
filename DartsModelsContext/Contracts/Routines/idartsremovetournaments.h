#ifndef IDARTSREMOVETOURNAMENTS_H
#define IDARTSREMOVETOURNAMENTS_H

#include <DartsModelsContext/Contracts/dartsmodelsservices.h>
#include <QVector>

class IDartsRemoveTournaments
{
public:
      typedef QVector<int> Indexes;
      virtual bool remove(const Indexes &indexes,
                          DartsModelsServices *services) = 0;
};

#endif // IDARTSREMOVETOURNAMENTS_H
