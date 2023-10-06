#include "dartsindexes.h"

#include <src/FileIO/filejsonio.h>

DartsIndexes::DartsIndexes()
{}

void DartsIndexes::init(const int& playerCount)
{
        _indexes = DartsIndex();
        _indexes.playersCount = playerCount;
}

void DartsIndexes::init()
{
        FileJsonIO jsonIO ("indexes.dat");
        _indexes = DartsIndex::fromJson(jsonIO.read());
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

int DartsIndexes::turnIndex()
{
        return _indexes.turnIndex;
}

const DartTurnIndex DartsIndexes::index() const
{
        return DartTurnIndex::fromIndex(_indexes);
}

void DartsIndexes::saveIndexes()
{
        FileJsonIO jsonIO("indexes.dat");
        jsonIO.write(_indexes.toJson());
}
