#include "dartsindexes.h"

#include <src/FileIO/filejsonio.h>

DartsIndexes::DartsIndexes()
{
        _indexesIO = new IndexesIO("indexes.dat");
}

void DartsIndexes::init(const int& playerCount)
{
        _indexes = DartsIndex();
        _indexes.playersCount = playerCount;
}

void DartsIndexes::init()
{
        _indexes = _indexesIO->loadIndexes();
}

bool DartsIndexes::next()
{
        _indexes.legIndex++;
        if(_indexes.legIndex > 2){
                _indexes.legIndex = 0;
                _indexes.playerIndex++;
                if(_indexes.playerIndex >= _indexes.playersCount)
                        _indexes.playerIndex = 0;
        }
        _indexes.totalTurns = ++_indexes.turnIndex;
        return true;
}

bool DartsIndexes::undo()
{
        if(_indexes.turnIndex < 1)
                return false;
        _indexes.legIndex--;
        if(_indexes.legIndex < 0){
                _indexes.legIndex = 2;
                _indexes.playerIndex--;
                if(_indexes.playerIndex < 0)
                        _indexes.playerIndex = _indexes.playersCount - 1;
        }
        _indexes.turnIndex--;
        return true;
}

bool DartsIndexes::redo()
{
        if(_indexes.turnIndex >= _indexes.totalTurns)
                return false;
        _indexes.legIndex++;
        if(_indexes.legIndex > 2){
                _indexes.legIndex = 0;
                _indexes.playerIndex++;
                if(_indexes.playerIndex >= _indexes.playersCount)
                        _indexes.playerIndex = 0;
        }
        _indexes.turnIndex++;
        return true;
}

bool DartsIndexes::canUndo()
{
        return _indexes.turnIndex > 0;
}

bool DartsIndexes::canRedo()
{
        return _indexes.turnIndex <  _indexes.totalTurns;
}

void DartsIndexes::reset()
{
        _indexes = DartsIndex();
}

int DartsIndexes::playerIndex()
{
        return _indexes.playerIndex;
}

bool DartsIndexes::saveState()
{
        return _indexesIO->saveIndexes(_indexes);
}

int DartsIndexes::turnIndex()
{
        return _indexes.turnIndex;
}

const DartsTurnIndex DartsIndexes::index() const
{
        return DartsTurnIndex(_indexes);
}
