#ifndef DARTSCORE_H
#define DARTSCORE_H

#include <qstring.h>

class DartScore
{
public:
        DartScore(const QString& playerName, int score) : _playerName(playerName),
                _score(score)
        {}

        int score() const
        {
                return _score;
        }

        QString playerName() const
        {
                return _playerName;
        }

private:
        QString _playerName;
        int _score;
};

#endif // DARTSCORE_H
