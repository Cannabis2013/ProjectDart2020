#include "dartsindexes.h"
#include "src/DartsController/turns/models/dartsturnindex.h"
#include "src/DartsController/turns/persistences/indexesio.h"

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
        auto count = _indexes.turnsLimit;
        _indexes = DartsIndex(count);
}

void DartsIndexes::next()
{
        nextThrow();
        _indexes.availableThrows = _indexes.throwCount;
}

void DartsIndexes::undo()
{
        if (!canUndo())
                return;
        if (--_indexes.throwIndex < 0) {
                _indexes.throwIndex = 2;
                if (--_indexes.turnIndex < 0) {
                        _indexes.turnIndex = _indexes.turnsLimit - 1;
                        _indexes.roundIndex--;
                }
        }
        _indexes.throwCount--;
}

void DartsIndexes::redo()
{
        if (!canRedo())
                return;
        nextThrow();
}

bool DartsIndexes::canUndo()
{
        return _indexes.throwCount > 0;
}

bool DartsIndexes::canRedo()
{
        return _indexes.throwCount < _indexes.availableThrows;
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
        auto index = 3 - _indexes.throwIndex;
        while (index-- > 0)
                next();
}

void DartsIndexes::nextThrow()
{
        _indexes.throwCount++;
        if (++_indexes.throwIndex > 2) {
                _indexes.turnId++;
                _indexes.throwIndex = 0;
                if (++_indexes.turnIndex >= _indexes.turnsLimit) {
                        _indexes.turnIndex = 0;
                        _indexes.roundIndex++;
                }
        }
}
