#include "dartsindexes.h"
#include <src/FileIO/filejsonio.h>

DartsIndexes::DartsIndexes()
{
        _indexesIO = new IndexesIO("indexes.dat");
}

void DartsIndexes::reset()
{
        auto count = _indexes.playersCount;
        _indexes = DartsIndex(count);
}

bool DartsIndexes::next()
{
        nextTurn();
        _indexes.totalTurns = ++_indexes.throwIndex;
        return true;
}

bool DartsIndexes::undo()
{
        if (!canUndo())
                return false;
        if (--_indexes.turnIndex < 0) {
                _indexes.turnIndex = 2;
                if (--_indexes.playerIndex < 0)
                        _indexes.playerIndex = _indexes.playersCount - 1;
        }
        _indexes.throwIndex--;
        return true;
}

bool DartsIndexes::redo()
{
        if (!canRedo())
                return false;
        nextTurn();
        _indexes.throwIndex++;
        return true;
}

void DartsIndexes::skipturn()
{
        auto index = 3 - _indexes.turnIndex;
        while (index-- > 0)
                next();
}

void DartsIndexes::nextTurn()
{
        if (++_indexes.turnIndex > 2) {
                _indexes.turnIndex = 0;
                if (++_indexes.playerIndex >= _indexes.playersCount)
                        _indexes.playerIndex = 0;
        }
}
