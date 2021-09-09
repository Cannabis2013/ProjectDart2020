#include "dcmeta.h"

using namespace DartsBuilderContext;

DCMeta::IdFormat DartsBuilderContext::DCMeta::tournamentId() const
{
    return _tournamentId;
}

int DartsBuilderContext::DCMeta::keyPoint() const
{
    return _keyPoint;
}

int DartsBuilderContext::DCMeta::attempts() const
{
    return _attempt;
}

int DartsBuilderContext::DCMeta::terminalKeyCode() const
{
    return _terminalKeyCode;
}

int DartsBuilderContext::DCMeta::inputHint() const
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

void DCMeta::setAttempt(int newAttempt)
{
    _attempt = newAttempt;
}

void DCMeta::setTerminalKeyCode(int newTerminalKeyCode)
{
    _terminalKeyCode = newTerminalKeyCode;
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
