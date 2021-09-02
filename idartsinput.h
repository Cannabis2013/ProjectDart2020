#ifndef IDARTSINPUT_H
#define IDARTSINPUT_H

#include "iplayerinput.h"

namespace ModelsContext{
    class   IDartsInput : public IPlayerInput
    {
    public:
        virtual int roundIndex() const = 0;
        virtual IDartsInput* setRoundIndex(const int &index) = 0;
        virtual int setIndex() const = 0;
        virtual IDartsInput* setSetIndex(const int &index) = 0;
        virtual int modKeyCode() const = 0;
        virtual IDartsInput* setModKeyCode(const int&) = 0;
        virtual int point() const = 0;
        virtual IDartsInput* setPoint(const int&) = 0;
        virtual int score() const = 0;
        virtual IDartsInput* setScore(const int&) = 0;
        virtual int attempt() const = 0;
        virtual IDartsInput* setAttempt(const int &) = 0;
    };
}

#endif // IDARTSINPUT_H
