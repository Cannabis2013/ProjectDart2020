#ifndef ITOURNAMENTJSONBUILDER_H
#define ITOURNAMENTJSONBUILDER_H

#include <qvector.h>

template<typename TTournament, typename TJson>
class ITournamentJsonBuilder
{
public:
    typedef TTournament Tournament;
    typedef TJson Json;
    virtual Json createJson(const QVector<const Tournament*> &tournaments) const = 0;
    virtual Json createJson(const Tournament* tournament) const = 0;
};
#endif // ICREATEJSONFROMDARTSTOURNAMENT_H
