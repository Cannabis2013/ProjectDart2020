#ifndef SCORECONTROLLER_H
#define SCORECONTROLLER_H

#include <qstring.h>
#include <qlist.h>
#include <QMultiHash>
#include <QRandomGenerator>

#include "ftplogisticcontrollerinterface.h"

#define TRIPPLE "T";
namespace PointLogisticContext{
    struct ScoreModel
    {
        QVector<char> multiplier;
        QVector<int> pointValue;
    };
}

class PointLogisticController : public FTPLogisticControllerInterface<QString>
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
    static PointLogisticController* createInstance(const int &numberOfAttemps,
                                                   const int &lastAttemptKeyCode);
    QString suggestTargetRow(const int &remainingScore, const int &turnIndex) override;
private:
    int lastAttemptKeyCode();
    /*
     * Private constructor
     */
    PointLogisticController(const int &throwCount, const int &finishingKeyCode);

    void constructAndAddSuggestions();
    QString constructThrowSuggestion(const int &remainingScore,
                                     const int &turnIndex,
                                     const int &route);
    bool pointSuggestion(const int &remainingScore,
                         const int &turnIndex,
                         PointLogisticContext::ScoreModel *scoreObject);

    int initializeLowerBound(int remainingScore, int multiplier);
    bool isDivisor(int base, int div);
    void updateScoreObject(char stringIdentifier, int value, int index, PointLogisticContext::ScoreModel *s);
    /*
     * Helper methods
     */
    bool evaluateConstraints(const int &remainingScore,
                             const int &turnIndex,
                             const int &totalTurns);
    bool isWithinTerminalThreshold(const int &remainingScore,
                                   const int &turnIndex,
                                   PointLogisticContext::ScoreModel *scoreObject);
    bool determineRouteByThresholdDiff(const int &remainingScore, const int &turnIndex, PointLogisticContext::ScoreModel *s);
    bool determineRouteByDiff(const int &remainingScore,
                              const int &turnIndex,
                              PointLogisticContext::ScoreModel *scoreObject);

    bool findLongestDivisibleWithinThreshold(const int &remainingScore,
                                             const int &turnIndex,
                                             const int &limit,
                                             const int &divisor,
                                             PointLogisticContext::ScoreModel *scoreObject);
    bool writeToScoreObject(const int &score,
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
    /*
     * Terminal conditions
     */
    int _terminalDivisor;
    int _terminalThreshold;
    /*
     *
     */
    const char identifiers[3] = {'S','D','T'};
    /*
     *
     */
    int _route;
    /*
     *
     */
    QList<QMultiHash<int,QString>> _throwSuggestions;
};


#endif // SCORECONTROLLER_H

