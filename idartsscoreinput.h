#ifndef IDARTSSCOREINPUT_H
#define IDARTSSCOREINPUT_H

#include "idartsinput.h"
#include <quuid.h>

namespace DartsModelsContext {
    class IDartsScoreInput :
            public IDartsInput
    {
    public:
        virtual int score() const = 0;
        virtual IDartsScoreInput* setScore(const int&) = 0;
    };
}

#endif // IDARTSSCOREINPUT_H
