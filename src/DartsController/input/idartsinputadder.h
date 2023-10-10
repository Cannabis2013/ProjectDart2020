#ifndef IDARTSINPUTADDER_H
#define IDARTSINPUTADDER_H

#include "src/DartsController/input/InputRequest.h"

class IDartsInputAdder {
public:
        virtual void add(const InputRequest& req) = 0;
};

#endif // IDARTSINPUTADDER_H
