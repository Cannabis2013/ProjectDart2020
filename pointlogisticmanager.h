#ifndef SCORECONTROLLER_H
#define SCORECONTROLLER_H

#include <qstring.h>
#include <qlist.h>
#include <QMultiHash>
#include <QRandomGenerator>

#include "ipointlogisticinterface.h"

#define TRIPPLE "T";

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
     * Create instanc
     */
    static PointLogisticManager* createInstance(const int &numberOfThrows,const int &lastThrowKeyCode);
    QString throwSuggestion(const int &remainingScore, const int &turnIndex) override;
    void setNumberOfThrows(const int &throwCount) override;
    void setLastThrowKeyCode(const int &keyCode) override;
    int lastThrowKeyCode() override;
private:
    /*
     * Private constructor
     */
    PointLogisticManager(const int &throwCount, const int &finishingKeyCode);

    void constructAndAddSuggestions();
    QString constructThrowSuggestion(const int &remainingScore, const int &turnIndex, const int &route);
    bool pointSuggestion(const int &remainingScore, const int &turnIndex, ScoreModel *scoreObject);

    int initializeLowerBound(int remainingScore, int multiplier);

    bool isDivisor(int base, int div);

    void updateScoreObject(char stringIdentifier, int value, int index, ScoreModel *s);
    /*
     * Helper methods
     */
    bool evaluteConstraints(const int &remainingScore, const int &turnIndex, const int &totalTurns);
    bool isWithinTerminalThreshold(const int &remainingScore, const int &turnIndex, ScoreModel *scoreObject);
    bool determineRouteByThresholdDiff(const int &remainingScore, const int &turnIndex, ScoreModel *s);
    bool determineRouteByDiff(const int &remainingScore, const int &turnIndex, ScoreModel *scoreObject);

    bool findLongestDivisibleWithinThreshold(const int &remainingScore, const int &turnIndex, const int &limit, const int &divisor, ScoreModel *scoreObject);
    bool writeToScoreObject(const int &score, const int &points, const int &divisor, const int &turnIndex, ScoreModel *s);
    QString toString(ScoreModel *s);

    int _throwCount;
    int _lastThrowKeyCode;

    const int _singleDivisor = 1;
    const int _doubleDivisor = 2;
    const int _trippleDivisor = 3;
    const int _upperThresholdValue = 110;
    const int _bull = 25;
    const int _bullsEye =  50;
    const int _singleMaxValue = 20;
    const int _doubleMaxValue = 40;
    const int _trippleMaxValue = 60;

    int _terminalDivisor;
    int _terminalThreshold;

    const char identifiers[3] = {'S','D','T'};

    int _route;

    QList<QMultiHash<int,QString>> _throwSuggestions;
};


#endif // SCORECONTROLLER_H

