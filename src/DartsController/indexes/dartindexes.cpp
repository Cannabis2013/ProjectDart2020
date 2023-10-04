#include "dartindexes.h"

#include <src/FileIO/filejsonio.h>

DartIndexes::DartIndexes()
{}

void DartIndexes::init(const int& playerCount)
{
        this->playersCount = playerCount;
}

void DartIndexes::initFromExternalContext(const int& playerCount)
{
        FileJsonIO jsonIO ("indexes.dat");
        _indexes = DartIndex::fromJson(jsonIO.read());
        this->playersCount = playerCount;
}

bool DartIndexes::next()
{
        _indexes.legIndex++;
        if(_indexes.legIndex > 2){
                _indexes.legIndex = 0;
                _indexes.playerIndex++;
                if(_indexes.playerIndex >= playersCount)
                        _indexes.playerIndex = 0;
        }
        _indexes.totalTurns = ++_indexes.turnIndex;
        return true;
}

bool DartIndexes::previous()
{
        if(_indexes.turnIndex < 1)
                return false;
        _indexes.legIndex--;
        if(_indexes.legIndex < 0){
                _indexes.legIndex = 2;
                _indexes.playerIndex--;
                if(_indexes.playerIndex < 0)
                        _indexes.playerIndex = playersCount - 1;
        }
        _indexes.turnIndex--;
        return true;
}

void DartIndexes::reset()
{
        _indexes = DartIndex();
}

int DartIndexes::turnIndex()
{
        return _indexes.turnIndex;
}

const DartTurnIndex DartIndexes::index() const
{
        return DartTurnIndex::fromIndex(_indexes);
}

void DartIndexes::saveIndexes()
{
        FileJsonIO jsonIO("indexes.dat");
        jsonIO.write(_indexes.toJson());
}
