#ifndef IDARTSPOINT_H
#define IDARTSPOINT_H

#include "idartsinput.h"

template <class TUuid>
class IDartsPointInput : public IDartsInput<TUuid>
{
public:

    virtual int modKeyCode() const = 0;
    virtual IDartsPointInput* setModKeyCode(const int&) = 0;
    virtual int point() const = 0;
    virtual IDartsPointInput* setPointValue(const int&) = 0;

    virtual int score() const = 0;
    virtual IDartsPointInput* setScoreValue(const int&) = 0;


    virtual int attempt() const = 0;
    virtual IDartsPointInput* setAttempt(const int &index) = 0;


};

#endif // IDARTSPOINT_H
