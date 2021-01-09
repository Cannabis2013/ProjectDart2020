#ifndef SCOREVALIDATORINTERFACE_H
#define SCOREVALIDATORINTERFACE_H

class ScoreValidatorInterface
{
public:
    virtual int evaluateScore(const int& currentScore,
                              const int& keyCode,
                              const int& input) const = 0;
};

#endif // SCOREVALIDATORINTERFACE_H
