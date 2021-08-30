#include "dcmetainfo.h"

using namespace DartsBuilderContext;

DCMetaInfo::IdFormat DartsBuilderContext::DCMetaInfo::tournamentId() const
{
    return _tournamentId;
}

int DartsBuilderContext::DCMetaInfo::keyPoint() const
{
    return _keyPoint;
}

int DartsBuilderContext::DCMetaInfo::attempts() const
{
    return _attempt;
}

int DartsBuilderContext::DCMetaInfo::terminalKeyCode() const
{
    return _terminalKeyCode;
}

int DartsBuilderContext::DCMetaInfo::inputHint() const
{
    return _inputHint;
}

void DCMetaInfo::setTournamentId(const IdFormat &newTournamentId)
{
    _tournamentId = newTournamentId;
}

void DCMetaInfo::setKeyPoint(int newKeyPoint)
{
    _keyPoint = newKeyPoint;
}

void DCMetaInfo::setAttempt(int newAttempt)
{
    _attempt = newAttempt;
}

void DCMetaInfo::setTerminalKeyCode(int newTerminalKeyCode)
{
    _terminalKeyCode = newTerminalKeyCode;
}

void DCMetaInfo::setInputHint(int newInputHint)
{
    _inputHint = newInputHint;
}

DCMetaInfo::IdFormat DCMetaInfo::winnerId() const
{
    return _winnerId;
}

void DCMetaInfo::setWinnerId(const IdFormat &newWinnerId)
{
    _winnerId = newWinnerId;
}

int DCMetaInfo::displayHint() const
{
    return _displayHint;
}

void DCMetaInfo::setDisplayHint(const int hint)
{
    _displayHint = hint;
}
