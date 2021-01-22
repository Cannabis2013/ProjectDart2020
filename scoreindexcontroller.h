#ifndef SCOREINDEXCONTROLLER_H
#define SCOREINDEXCONTROLLER_H

#include <qvector.h>
#include "indexcontrollerinterface.h"

class ScoreIndexController : public IndexControllerInterface
{
public:
    // Create instance
    static ScoreIndexController* createInstance(const int &playerCount,
                                                const QVector<int> &indexes);
    // IndexControllerInterface interface
    virtual void reset() override;
    virtual void next() override;
    virtual void undo() override;
    virtual void redo() override;
    virtual bool canUndo() override;
    virtual bool canRedo() override;
    virtual void syncIndex() override;
    virtual int index() override;
    virtual int totalIndex() override;
    virtual int roundIndex() override;
    virtual int setIndex() override;
    virtual int legIndex() override;

private:
    // Private methods
    void incrementTurnIndex();
    void incrementRoundIndex();
    void incrementSetIndex();
    void resetSetIndex();
    void resetLegIndex();
    int playerCount();
    int lastPlayerIndex();

    ScoreIndexController(const int &playerCount, const QVector<int>& indexes);
    int _index = 0, _totalIndex  = 0, _roundIndex = 1, _setIndex = 0, _legIndex = 0;
    const int _legCount = -1, _playerCount;
};

#endif // SCOREINDEXCONTROLLER_H
