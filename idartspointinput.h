#ifndef IDARTSPOINT_H
#define IDARTSPOINT_H

#include "idartsinput.h"

namespace DartsModelsContext
{
    class IDartsPointInput : public DartsModelsContext::IDartsInput
    {
    public:

        virtual int modKeyCode() const = 0;
        virtual DartsModelsContext::IDartsPointInput* setModKeyCode(const int&) = 0;
        virtual int point() const = 0;
        virtual DartsModelsContext::IDartsPointInput* setPoint(const int&) = 0;
        virtual int score() const = 0;
        virtual DartsModelsContext::IDartsPointInput* setScore(const int&) = 0;
        virtual int attempt() const = 0;
        virtual DartsModelsContext::IDartsPointInput* setAttempt(const int &) = 0;
    };
}


#endif // IDARTSPOINT_H
