#include "inputsdb.h"
#include <DartsStatistics/Contracts/Inputs/Models/snapshot.h>

void InputStatistics::add(const Model &model)
{
    _models.append(model);
}

void InputStatistics::add(const Models &models)
{
        for (const auto &model : models)
                _models.append(model);
}

InputStatistics::Model &InputStatistics::model(const int &index)
{
    return _models[index];
}

InputStatistics::Model &InputStatistics::model(Pred predFunc)
{
    for (int i = 0; i < _models.count(); ++i) {
        auto model = _models.at(i);
        if(predFunc(model))
            return _models[i];
    }
    throw new std::out_of_range("Model not in db");
}

QVector<InputStatistics::Model> InputStatistics::models() const
{
    return _models;
}

QVector<InputStatistics::Model> InputStatistics::models(Pred predFunc) const
{
    QVector<SnapShot> inputs;
    for (const auto &model : _models) {
        if(predFunc(model))
            inputs << model;
    }
    return inputs;
}

void InputStatistics::remove(const int &index)
{
    _models.remove(index);
}

void InputStatistics::remove(const QVector<int> &indexes)
{

    for (int i = indexes.count() - 1; i >= 0; --i)
        _models.remove(indexes.at(i));
}

void InputStatistics::clear()
{
    _models.clear();
}

int InputStatistics::indexOf(const Model &model) const
{
    for (int i = 0; i < _models.count(); ++i) {
        auto m = _models.at(i);
        if (m.keyCode == model.keyCode) return i;
    }
    return -1;
}

void InputStatistics::replace(const int &index, const Model &model)
{
    _models.replace(index,model);
}
