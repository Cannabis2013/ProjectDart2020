#include "dcmeta.h"

using namespace DCBuilding;

DCMeta::IdFormat DCBuilding::DCMeta::tournamentId() const
{
    return _tournamentId;
}

int DCBuilding::DCMeta::keyPoint() const
{
    return _keyPoint;
}

int DCBuilding::DCMeta::inputHint() const
{
    return _inputHint;
}

void DCMeta::setTournamentId(const IdFormat &newTournamentId)
{
    _tournamentId = newTournamentId;
}

void DCMeta::setKeyPoint(int newKeyPoint)
{
    _keyPoint = newKeyPoint;
}

void DCMeta::setInputHint(int newInputHint)
{
    _inputHint = newInputHint;
}

DCMeta::IdFormat DCMeta::winnerId() const
{
    return _winnerId;
}

void DCMeta::setWinnerId(const IdFormat &newWinnerId)
{
    _winnerId = newWinnerId;
}

int DCMeta::displayHint() const
{
    return _displayHint;
}

void DCMeta::setDisplayHint(const int hint)
{
    _displayHint = hint;
}
