#ifndef IDARTSINPUT_H
#define IDARTSINPUT_H

#include "DartsModelsContext/InputsDbSLAs/iplayerinput.h"
#include "DartsModelsContext/InputsDbModels/dartsinputstats.h"

namespace ModelsContext{
    class   IDartsInput : public IPlayerInput, public DartsInputStats
    {
    public:
        virtual int modKeyCode() const = 0;
        virtual IDartsInput* setModKeyCode(const int&) = 0;
        virtual int point() const = 0;
        virtual IDartsInput* setPoint(const int&) = 0;
        virtual int score() const = 0;
        virtual IDartsInput* setScore(const int&) = 0;
        virtual int remainingScore() const = 0;
        virtual IDartsInput *setRemainingScore(const int &score) = 0;
        virtual int roundIndex() const = 0;
        virtual IDartsInput* setRoundIndex(const int &index) = 0;
        virtual int setIndex() const = 0;
        virtual IDartsInput* setSetIndex(const int &index) = 0;
        virtual int attempt() const = 0;
        virtual IDartsInput* setAttempt(const int &) = 0;
    };
}
#endif // IDARTSINPUT_H
