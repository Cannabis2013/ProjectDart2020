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
    };
}

#endif // IDARTSINPUT_H
