#include "dartsindexes.h"
#include "src/DartsController/turns/models/dartsturnindex.h"
#include <src/FileIO/filejsonio.h>

DartsIndexes::DartsIndexes()
{
        _indexesIO = new IndexesIO();
}

void DartsIndexes::init(const int& playerCount)
{
        _indexes = DartsIndex(playerCount);
}

void DartsIndexes::initFromFile()
{
        _indexes = _indexesIO->loadIndexes();
}

void DartsIndexes::reset()
{
        auto count = _indexes.playersCount;
        _indexes = DartsIndex(count);
}

void DartsIndexes::next()
{
        nextTurn();
        _indexes.totalThrows = ++_indexes.currentThrows;
}

void DartsIndexes::undo()
{
        if (!canUndo())
                return;
        if (--_indexes.currentThrowIndex < 0) {
                _indexes.currentThrowIndex = 2;
                if (--_indexes.currentTurnIndex < 0) {
                        _indexes.currentTurnIndex = _indexes.playersCount - 1;
                        _indexes.currentThrowId--;
                }
        }
        _indexes.currentThrows--;
}

void DartsIndexes::redo()
{
        if (!canRedo())
                return;
        nextTurn();
        _indexes.currentThrows++;
}

bool DartsIndexes::canUndo()
{
        return _indexes.currentThrows > 0;
}

bool DartsIndexes::canRedo()
{
        return _indexes.currentThrows < _indexes.totalThrows;
}

bool DartsIndexes::saveState()
{
        return _indexesIO->saveIndexes(_indexes);
}

const DartsTurnIndex DartsIndexes::index() const
{
        return DartsTurnIndex(_indexes);
}

void DartsIndexes::skipturn()
{
        auto index = 3 - _indexes.currentThrowIndex;
        while (index-- > 0)
                next();
}

void DartsIndexes::nextTurn()
{
        if (++_indexes.currentThrowIndex > 2) {
                _indexes.currentThrowIndex = 0;
                if (++_indexes.currentTurnIndex >= _indexes.playersCount) {
                        _indexes.currentTurnIndex = 0;
                        _indexes.currentThrowId++;
                }
        }
}
