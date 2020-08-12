#ifndef SCORECONTROLLER_H
#define SCORECONTROLLER_H

#include <qstring.h>
#include <qlist.h>

#include "ipointlogisticinterface.h"

#define TRIPPLE "T";

const int Bull = 25;
const int BullsEye =  50;
const int singleMaxValue = 20;
const int doubleMaxValue = 40;
const int trippleMaxValue = 60;

struct ScoreModel
{
    QVector<char> multiplier;
    QVector<int> pointValue;
};

class PointLogisticManager : public IPointLogisticInterface<QString>
{
public:

    /*
     * Public types
     */
    enum KeyMappings{
        SingleModifer = 0x2A,
        DoubleModifier = 0x2B,
        TrippleModifier = 0x2C
    };
    /*
     * Constructor
     */
    PointLogisticManager(const int &throwCount = 3, const int &finishingKeyCode = KeyMappings::DoubleModifier)
    {
        _throwCount = throwCount;

        _lastThrowKeyCode = finishingKeyCode;
        _terminalThreshold = _lastThrowKeyCode == KeyMappings::SingleModifer
                ? singleMaxValue : _lastThrowKeyCode == KeyMappings::DoubleModifier ?
                      doubleMaxValue :
                                                                                                                                      trippleMaxValue;
        _terminalDivisor = _lastThrowKeyCode == KeyMappings::SingleModifer ?
                    1 :_lastThrowKeyCode == KeyMappings::DoubleModifier ?
                        2 : 3;

    }
    QString constructThrowSuggestions(const int &remainingScore, const int &turnIndex) override;
    void setNumberOfThrows(const int &throwCount) override
    {
        _throwCount = throwCount;
    }

    void setLastThrowKeyCode(const int &keyCode) override
    {
        _lastThrowKeyCode = keyCode;
    }
    int lastThrowKeyCode() override
    {
        return _lastThrowKeyCode;
    }
private:
    bool pointSuggestion(const int &remainingScore,const int &turnIndex, ScoreModel *scoreObject);

    int initializeLowerBound(int remainingScore, int multiplier)
    {
        if(remainingScore < multiplier)
            return 0;

        auto rest = remainingScore % multiplier;

        return remainingScore - rest;
    }

    bool isDivisor(int base, int div)
    {
        if(base == 0 || div == 0)
            throw new std::domain_error("One of operands zero");

        return base % div == 0;
    }

    void updateScoreObject(char stringIdentifier, int value, int index, ScoreModel *s)
    {
        if(value < 0)
            throw new std::out_of_range("Value out of bounds");

        s->multiplier[index - 1] = stringIdentifier;
        s->pointValue[index - 1] = value;
    }

    bool isWithinTerminalThreshold(const int &remainingScore, const int &turnIndex, ScoreModel *scoreObject);
    bool isWithinUpperThreshold(const int &remainingScore, const int &turnIndex, ScoreModel *s);
    bool isDiffWithinReach(const int &remainingScore, const int &turnIndex, ScoreModel *scoreObject);
    QString toString(ScoreModel *s);

    int _throwCount;
    int _lastThrowKeyCode;

    const int doubleDivisor = 2;
    const int trippleDivisor = 3;
    const int upperThresholdValue = 110;

    int _terminalDivisor;
    int _terminalThreshold;

    const char identifiers[3] = {'S','D','T'};
};
#endif // SCORECONTROLLER_H

