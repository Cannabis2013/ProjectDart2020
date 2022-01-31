#ifndef IDARTSRESETTOURNAMENT_H
#define IDARTSRESETTOURNAMENT_H
class QUuid;
class IDartsResetTournament
{
public:
    virtual void reset(const QUuid &tournamentID) const = 0;
};
#endif // IDARTSRESETTOURNAMENT_H
