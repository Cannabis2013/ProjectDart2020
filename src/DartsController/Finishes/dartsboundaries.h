#ifndef DARTSBOUNDARIES_H
#define DARTSBOUNDARIES_H

class DartsBoundaries
{
public:
    int trippleMaxValue() const { return _trippleMaxValue; }
    int doubleMaxValue() const { return _doubleMaxValue; }
    int singleMaxValue() const { return _singleMaxValue; }

private:
    const int _singleMaxValue = 20;
    const int _doubleMaxValue = 40;
    const int _trippleMaxValue = 60;
};
#endif // DARTSBOUNDARIES_H
