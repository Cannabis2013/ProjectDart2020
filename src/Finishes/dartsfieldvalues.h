#ifndef DARTSFIELDVALUES_H
#define DARTSFIELDVALUES_H

class DartsFieldValues
{
public:
    int bullsEye() const { return _bullsEye; }
    int bull() const { return _bull; }

private:
    const int _bull = 25;
    const int _bullsEye =  50;
};
#endif // DARTSFIELDVALUES_H
