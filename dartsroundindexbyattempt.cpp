#include "dartsroundindexbyattempt.h"


int DartsRoundIndexByAttempt::roundByAttempt(const int &index) const
{
    auto roundIndex = (index - 1)/_numberOfAttempts + 1;
    return index != 0 ? roundIndex : _initialRound;
}

int DartsRoundIndexByAttempt::numberOfAttempts() const
{
    return _numberOfAttempts;
}

void DartsRoundIndexByAttempt::setNumberOfAttempts(int newNumberOfAttempts)
{
    _numberOfAttempts = newNumberOfAttempts;
}

int DartsRoundIndexByAttempt::initialRound() const
{
    return _initialRound;
}

void DartsRoundIndexByAttempt::setInitialRound(int newInitialRound)
{
    _initialRound = newInitialRound;
}
