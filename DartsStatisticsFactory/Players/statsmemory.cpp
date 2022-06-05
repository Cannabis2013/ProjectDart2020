#include "statsmemory.h"
#include <DartsStatistics/Players/Models/currentstats.h>

void StatsMemory::add(const Model &model)
{
    _mirrors.append(model);
}

void StatsMemory::add(const Models &models)
{
        for (const auto &model : models)
                _mirrors.append(model);
}

StatsMemory::Model &StatsMemory::model(const int &index)
{
        return _mirrors[index];
}

StatsMemory::Model &StatsMemory::model(Pred prefFunc)
{
        for (int i = 0; i < _mirrors.count(); ++i) {
                auto m = _mirrors[i];
                if(prefFunc(m))
                        return _mirrors[i];
        }
        throw new std::out_of_range("Model not in db");
}

StatsMemory::Models StatsMemory::models() const
{
        return _mirrors;
}

StatsMemory::Models StatsMemory::models(Pred predFunc) const
{
        QVector<CurrentStat> mirrors;
        for (const auto &mirror : _mirrors) {
            if(predFunc(mirror))
                mirrors << mirror;
        }
        return mirrors;
}

void StatsMemory::remove(const int &index)
{
         _mirrors.remove(index);
}

void StatsMemory::remove(const QVector<int> &indexes)
{
        for (int i = indexes.count() - 1; i >= 0; --i) {
                auto index = indexes.at(i);
                _mirrors.remove(index);
        }
}

void StatsMemory::clear()
{
        _mirrors.clear();
}

int StatsMemory::indexOf(const Model &model) const
{
        for (int i = 0; i < _mirrors.count(); ++i) {
                auto m = _mirrors.at(i);
                if(m.name == model.name)
                    return i;
        }
        return -1;
}

void StatsMemory::replace(const int &index, const Model &model)
{
        _mirrors.replace(index,model);
}
