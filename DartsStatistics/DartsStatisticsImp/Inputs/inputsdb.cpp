#include "inputsdb.h"
#include <DartsStatistics/Contracts/Inputs/Models/snapshot.h>

void InputsDb::add(const Model &model)
{
    _models.append(model);
}

void InputsDb::add(const Models &models)
{
        for (const auto &model : models)
                _models.append(model);
}

InputsDb::Model &InputsDb::model(const int &index)
{
    return _models[index];
}

InputsDb::Model &InputsDb::model(Pred predFunc)
{
    for (int i = 0; i < _models.count(); ++i) {
        auto model = _models.at(i);
        if(predFunc(model))
            return _models[i];
    }
    throw new std::out_of_range("Model not in db");
}

QVector<InputsDb::Model> InputsDb::models() const
{
    return _models;
}

QVector<InputsDb::Model> InputsDb::models(Pred predFunc) const
{
    QVector<SnapShot> inputs;
    for (const auto &model : _models) {
        if(predFunc(model))
            inputs << model;
    }
    return inputs;
}

void InputsDb::remove(const int &index)
{
    _models.remove(index);
}

void InputsDb::remove(const QVector<int> &indexes)
{

    for (int i = indexes.count() - 1; i >= 0; --i)
        _models.remove(indexes.at(i));
}

void InputsDb::clear()
{
    _models.clear();
}

int InputsDb::indexOf(const Model &model) const
{
    for (int i = 0; i < _models.count(); ++i) {
        auto m = _models.at(i);
        if(m.name == model.keyCode)
            return i;
    }
    return -1;
}

void InputsDb::replace(const int &index, const Model &model)
{
    _models.replace(index,model);
}
