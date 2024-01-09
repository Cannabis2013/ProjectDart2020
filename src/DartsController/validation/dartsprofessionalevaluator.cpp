#include "dartsprofessionalevaluator.h"

DartsProfessionalEvaluator::DartsProfessionalEvaluator(IDartsScores* scores, IDartsPlayers* players, IDartsStatus* status, IScoresCalculator* calculator, IPlayerAllowances* allowances)
    : _scores(scores)
    , _players(players)
    , _status(status)
    , _calculator(calculator)
    , _allowances(allowances)
{
}

bool DartsProfessionalEvaluator::evaluateInput(const QString& mod, const int& point)
{
        auto name = _players->player().name();
        if (!validateInput(name, mod, point))
                return false;
        auto playerScore = _scores->score().playerScore();
        return validateRemaining(mod, point, playerScore);
}

void DartsProfessionalEvaluator::evaluateWinnerCondition()
{
        auto scores = _scores->scores().playerScores();
        for (const auto& score : scores) {
                if (score.score() == 0) {
                        _status->winnerFound();
                        auto winner = &_players->player(score.name());
                        winner->setWinner(true);
                }
        }
}

bool DartsProfessionalEvaluator::validateInput(const QString& name, const QString& mod, const int& point)
{
        if (!_calculator->isValid(point, mod))
                return false;
        if (_allowances->isAllowed(name))
                return true;
        if (mod == "D")
                return _allowances->updateAllowance(name, true);
        return false;
}

bool DartsProfessionalEvaluator::validateRemaining(const QString& mod, const int& point, const int& current)
{
        auto remaining = _calculator->remaining(mod, point, current);
        if (remaining > 1)
                return true;
        else if (remaining == 0 && (mod == "D" || point == 50))
                return true;
        return false;
}
