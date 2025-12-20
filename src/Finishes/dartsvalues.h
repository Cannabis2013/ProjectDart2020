#ifndef DARTSVALUES_H
#define DARTSVALUES_H

class DartsValues
{
  public:
    int trippleMaxValue() const { return _trippleMaxValue; }
    int doubleMaxValue() const { return _doubleMaxValue; }
    int singleMaxValue() const { return _singleMaxValue; }
    int terminalThreshold() const { return _terminal_threshold; }
    int upperThresholdValue() const { return _upper_threshold; }
    int trippleDivisor() const { return _trippleDivisor; }
    int doubleDivisor() const { return _doubleDivisor; }
    int singleDivisor() const { return _singleDivisor; }
    int bullsEye() const { return _bullsEye; }
    int bull() const { return _bull; }
    char identifierByDivisor(const int &divisor) const
    {
        if (divisorValid(divisor))
            return identifiers[formattedDivisor(divisor)];
        throw "Divisor not valid";
    }

  private:
    int formattedDivisor(const int &divisor) const { return divisor - 1; }

    bool divisorValid(const int &divisor) const { return divisor >= 1 && divisor <= 3; }

    const char identifiers[3] = {'S', 'D', 'T'};
    const int _singleMaxValue = 20;
    const int _doubleMaxValue = 40;
    const int _trippleMaxValue = 60;
    const int _terminal_threshold = 40;
    const int _upper_threshold = 110;
    const int _singleDivisor = 1;
    const int _doubleDivisor = 2;
    const int _trippleDivisor = 3;
    const int _bull = 25;
    const int _bullsEye = 50;
};
#endif // DARTSVALUES_H
