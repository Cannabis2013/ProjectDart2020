#ifndef IDARTSADDTOURNAMENT_H
#define IDARTSADDTOURNAMENT_H

#include <DartsModelsContext/Contracts/dartsmodelsservices.h>
#include <QVector>

class IDartsAddTournament
{
public:
      typedef QVector<int> Indexes;
      typedef DartsModelsServices Services;
      virtual bool add(const QByteArray &byteArray, const Indexes &indexes,
                       Services *services) = 0;
};

#endif // IDARTSADDTOURNAMENT_H
