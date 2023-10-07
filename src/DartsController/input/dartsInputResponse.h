#ifndef DARTSINPUTRESPONSE_H
#define DARTSINPUTRESPONSE_H

#include "src/DartsController/input/Input.h"
#include <QString>

class DartsInputResponse{
public:
    DartsInputResponse(const Input &input)
        {
                _mod = input.mod();
                _point = input.point();
        }

        int point() const { return _point; }
        QString mod() const {return _mod;}
private:
        int _point = -1;
        QString _mod = "S";
};



#endif // DARTSINPUTRESPONSE_H
