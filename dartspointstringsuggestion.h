#ifndef DARTSPOINTSTRINGSUGGESTION_H
#define DARTSPOINTSTRINGSUGGESTION_H

#include "idartsinputsuggestion.h"
#include <qstring.h>
#include <QMultiHash>
#include <QRandomGenerator>

namespace PointLogisticContext
{
    struct ScoreModel
    {
        QVector<char> multiplier;
        QVector<int> pointValue;
    };
}

class DartsPointStringSuggestion : public IDartsInputSuggestion
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
    // Create instance
    static DartsPointStringSuggestion* createInstance(const int& attemps,
                                                      const int& lastAttemptKeyCode = DoubleModifier);
    // FTPLogisticControllerInterface interface
    virtual QString suggestTargetRow(const int &remainingScore, const int &turnIndex) const override;
private:
    bool isEven(const int& integer);
    int terminalDivisor() const;
    int terminalThreshold() const;
    // Const values
    int trippleMaxValue() const;
    int doubleMaxValue() const;
    int singleMaxValue() const;
    int bullsEye() const;
    int bull() const;
    int upperThresholdValue() const;
    int trippleDivisor() const;
    int doubleDivisor() const;
    int singleDivisor() const;
    virtual int lastAttemptKeyCode();
    int attempts() const;
    // Private constructor
    DartsPointStringSuggestion(const int& attempts, const int& lastAttemptKeyCode);

    void constructAndAddSuggestions();
    QString constructThrowSuggestion(const int &remainingScore,
                                     const int &turnIndex);
    bool pointSuggestion(const int &remainingScore,
                         const int &turnIndex,
                         PointLogisticContext::ScoreModel *scoreObject);

    bool evaluateConstraints(const int &remainingScore,
                             const int &turnIndex,
                             const int &totalTurns);
    bool isWithinTerminalThreshold(const int &remainingScore,
                                   const int &turnIndex,
                                   PointLogisticContext::ScoreModel *scoreObject);
    bool isDivisor(int base, int div);
    bool determineRouteByThresholdDiff(const int &remainingScore, const int &turnIndex, PointLogisticContext::ScoreModel *s);
    bool determineRouteByDiff(const int &remainingScore, const int &turnIndex, PointLogisticContext::ScoreModel *scoreObject);
    bool findGreatestPointsWithinThreshold(const int &remainingScore,
                                             const int &turnIndex,
                                             const int &threshold,
                                             const int &divisor,
                                             PointLogisticContext::ScoreModel *s);
    bool findGreatestPointsWithinTerminalThreshold(const int &remainingScore,
                                         const int &turnIndex,
                                         const int &threshold,
                                         PointLogisticContext::ScoreModel *s);
    bool findGreatestOddDivisibleByThree(const int &remainingScore,
                                         const int &turnIndex,
                                         PointLogisticContext::ScoreModel* s);
    void updateScoreObject(char stringIdentifier,
                           int value,
                           int index,
                           PointLogisticContext::ScoreModel *s);
    bool writeToScoreObject(const int &remainingScore,
                            const int &points,
                            const int &divisor,
                            const int &turnIndex, PointLogisticContext::ScoreModel *s);
    QString toString(PointLogisticContext::ScoreModel *s);

    const int _attempts;
    const int _lastAttemptKeyCode;

    const int _singleDivisor = 1;
    const int _doubleDivisor = 2;
    const int _trippleDivisor = 3;
    /*
     * The upper threshold by two remaining turns.
     *
     *  - You must finish with either a double or bullseye
     *  - That means, a max row to finish is: T20 - bullseye = 110 points
     */
    const int _upperThresholdValue = 110;
    const int _bull = 25;
    const int _bullsEye =  50;
    const int _singleMaxValue = 20;
    const int _doubleMaxValue = 40;
    const int _trippleMaxValue = 60;

    int _terminalDivisor;
    int _terminalThreshold;

    const char identifiers[3] = {'S','D','T'};


    QList<QMultiHash<int,QString>> _throwSuggestions;
};
#endif // SCORECONTROLLER_H

