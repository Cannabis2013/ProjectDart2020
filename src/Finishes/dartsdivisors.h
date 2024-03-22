#ifndef DARTSDIVISORS_H
#define DARTSDIVISORS_H

class DartsDivisors
{
public:
    int trippleDivisor() const { return _trippleDivisor; }
    int doubleDivisor() const { return _doubleDivisor; }
    int singleDivisor() const { return _singleDivisor; }

private:
    const int _singleDivisor = 1;
    const int _doubleDivisor = 2;
    const int _trippleDivisor = 3;
};
#endif // DARTSDIVISORS_H
