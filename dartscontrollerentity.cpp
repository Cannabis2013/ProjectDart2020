#include "dartscontrollerentity.h"

using namespace DartsBuilderContext;

DartsControllerEntity::IdFormat DartsBuilderContext::DartsControllerEntity::tournamentId() const
{
    return _tournamentId;
}

int DartsBuilderContext::DartsControllerEntity::keyPoint() const
{
    return _keyPoint;
}

int DartsBuilderContext::DartsControllerEntity::attempts() const
{
    return _attempt;
}

int DartsBuilderContext::DartsControllerEntity::terminalKeyCode() const
{
    return _terminalKeyCode;
}

int DartsBuilderContext::DartsControllerEntity::inputHint() const
{
    return _inputHint;
}

void DartsControllerEntity::setTournamentId(const IdFormat &newTournamentId)
{
    _tournamentId = newTournamentId;
}

void DartsControllerEntity::setKeyPoint(int newKeyPoint)
{
    _keyPoint = newKeyPoint;
}

void DartsControllerEntity::setAttempt(int newAttempt)
{
    _attempt = newAttempt;
}

void DartsControllerEntity::setTerminalKeyCode(int newTerminalKeyCode)
{
    _terminalKeyCode = newTerminalKeyCode;
}

void DartsControllerEntity::setInputHint(int newInputHint)
{
    _inputHint = newInputHint;
}

DartsControllerEntity::IdFormat DartsControllerEntity::winnerId() const
{
    return _winnerId;
}

void DartsControllerEntity::setWinnerId(const IdFormat &newWinnerId)
{
    _winnerId = newWinnerId;
}

int DartsControllerEntity::displayHint() const
{
    return _displayHint;
}

void DartsControllerEntity::setDisplayHint(const int hint)
{
    _displayHint = hint;
}
