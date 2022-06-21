#ifndef IDARTSRESETTOURNAMENT_H
#define IDARTSRESETTOURNAMENT_H

class DartsModelsServices;
class QUuid;

class IDartsResetTournament
{
public:
    virtual bool reset(const QUuid &tournamentID, DartsModelsServices *services) = 0;
};
#endif // IDARTSRESETTOURNAMENT_H
