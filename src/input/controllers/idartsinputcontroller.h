#ifndef IDARTSINPUTCONTROLLER_H
#define IDARTSINPUTCONTROLLER_H

#include <qstring.h>

class IDartsInputController {
public:
        virtual void add(const QByteArray& inputs) = 0;
};

#endif // IDARTSINPUTCONTROLLER_H
