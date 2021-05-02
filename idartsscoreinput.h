#ifndef IDARTSSCOREINPUT_H
#define IDARTSSCOREINPUT_H

#include "idartsinput.h"
template<typename TUuid>
class IDartsScoreInput : public IDartsInput<TUuid>
{
public:
    IDartsScoreInput() {}

    virtual int score() const = 0;
    virtual IDartsScoreInput* setScore(const int&) = 0;
};

#endif // IDARTSSCOREINPUT_H
