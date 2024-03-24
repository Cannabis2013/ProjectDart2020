#include "dartsindexes.h"
#include "src/turns/models/dartsturnindex.h"
#include "src/turns/persistences/indexesio.h"

DartsIndexes::DartsIndexes()
{
        _indexesIO = new IndexesIO();
}

void DartsIndexes::init()
{
        _indexes = DartsIndex();
}

void DartsIndexes::initFromFile()
{
        _indexes = _indexesIO->loadIndexes();
}

void DartsIndexes::reset()
{
        _indexes = DartsIndex();
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
        if (--_indexes.turnIndex < 0) {
                _indexes.turnIndex = _indexes.turnsLimit - 1;
                _indexes.roundIndex--;
        }
        _indexes.turnCount--;
        _indexes.throwCount -= 3;
}

void DartsIndexes::redo()
{
        if (!canRedo())
                return;
        nextThrow();
}

bool DartsIndexes::canUndo()
{
        return _indexes.throwCount >= 3;
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

void DartsIndexes::nextThrow()
{
        _indexes.throwCount += 3;
        _indexes.turnCount++;
        if (++_indexes.turnIndex >= _indexes.turnsLimit) {
                _indexes.turnIndex = 0;
                _indexes.roundIndex++;
        }
}
