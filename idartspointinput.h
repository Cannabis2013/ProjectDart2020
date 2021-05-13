#ifndef IDARTSPOINT_H
#define IDARTSPOINT_H

#include "idartsinput.h"
#include <quuid.h>

class IDartsPointInput : public IDartsInput
{
public:

    virtual int modKeyCode() const = 0;
    virtual IDartsPointInput* setModKeyCode(const int&) = 0;
    virtual int point() const = 0;
    virtual IDartsPointInput* setPoint(const int&) = 0;
    virtual int score() const = 0;
    virtual IDartsPointInput* setScore(const int&) = 0;
    virtual int attempt() const = 0;
    virtual IDartsPointInput* setAttempt(const int &) = 0;
};

#endif // IDARTSPOINT_H
