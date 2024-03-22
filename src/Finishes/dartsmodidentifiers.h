#ifndef DARTSMODIDENTIFIERS_H
#define DARTSMODIDENTIFIERS_H

class DartsModIdentifiers
{
public:
    char identifierByDivisor(const int &divisor) const
    {
        if (divisorValid(divisor))
            return identifiers[formattedDivisor(divisor)];
        throw "Divisor not valid";
        }
private:
        int formattedDivisor(const int &divisor) const
        {
                return divisor - 1;
        }

        bool divisorValid(const int &divisor) const
        {
                return divisor >= 1 && divisor <= 3;
        }

        const char identifiers[3] = {'S','D','T'};
};

#endif // DARTSIDENTIFIERS_H
