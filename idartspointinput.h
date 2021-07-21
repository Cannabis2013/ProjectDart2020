#ifndef IDARTSPOINT_H
#define IDARTSPOINT_H

#include "idartsinput.h"

namespace ModelsContext
{
    class IDartsPointInput : public ModelsContext::IDartsInput
    {
    public:

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


#endif // IDARTSPOINT_H
