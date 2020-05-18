#include "localdatacontext.h"

const DefaultTournamentInterface *LocalDataContext::getTournamentFromID(const QUuid &id) const
{
    for (auto tournament : _tournaments) {
        if(tournament->id() == id)
            return tournament;
    }

    throw THROW_OBJECT_WITH_ID_NOT_FOUND(id.toString());
}

const DefaultRoundInterface *LocalDataContext::getRoundFromID(const QUuid &id) const
{
    for (auto round : _rounds) {
        if(round->id() == id)
            return round;
    }

    throw THROW_OBJECT_WITH_ID_NOT_FOUND(id.toString());
}

const DefaultSetInterface *LocalDataContext::getSetFromID(const QUuid &id) const
{
    for (auto set : _sets)
    {
        if(set->id() == id)
            return set;
    }

    throw THROW_OBJECT_WITH_ID_NOT_FOUND(id.toString());
}

const DefaultPointInterface *LocalDataContext::getPointFromID(const QUuid &id) const
{
    for (auto point : _points)
    {
        if(point->id() == id)
            return point;
    }

    throw THROW_OBJECT_WITH_ID_NOT_FOUND(id.toString());
}

void LocalDataContext::removeTournamentModel(const QUuid &tournament)
{
    for (int i = 0; i < _tournaments.count(); ++i) {
        auto model = _tournaments.at(i);
        auto id = model->id();
        if(id == tournament)
        {
            _tournaments.removeAt(i);
            return;
        }
    }
}

void LocalDataContext::removePointModel(const QUuid &point)
{
    for (int i = 0; i < _points.count(); ++i) {
        auto model = _points.at(i);
        auto id = model->id();
        if(id == point)
        {
            _points.removeAt(i);
            return;
        }
    }
}

ITournamentBuilder *LocalDataContext::tournamentBuilder() const
{

}

IRoundBuilder *LocalDataContext::roundBuilder() const
{

}

ISetBuilder *LocalDataContext::setBuilder() const
{

}

IPointBuilder *LocalDataContext::pointBuilder() const
{

}
