#ifndef DARTSPLAYERDATAMODEL_H
#define DARTSPLAYERDATAMODEL_H
#include <qobject.h>
#include "iheaderlabels.h"
#define OUT_OF_RANGE_MSG "Index out of range";
#define ITEM_NOT_FOUND_MSG "Item not found";
class DartsPlayerDataModel : public QObject
{
    Q_OBJECT
public:
    Q_INVOKABLE void addPlayer(const QString &playerName)
    {
        Model m;
        m.playerName = playerName;
        _models << m;
        emit dataChanged(indexOf(playerName));
    }
    Q_INVOKABLE QString playerName(const int &index) const
    {
        return _models.at(index).playerName;
    }
    Q_INVOKABLE void setMin(const QString &playerName, const int &value)
    {
        auto m = &model(playerName);
        m->min = value;
        emit dataChanged(indexOf(playerName));
    }
    Q_INVOKABLE void setMid(const QString &playerName, const double &value)
    {
        auto m = &model(playerName);
        m->mid = value;
        emit dataChanged(indexOf(playerName));
    }
    Q_INVOKABLE void setMax(const QString &playerName, const int &value)
    {
        auto m = &model(playerName);
        m->max = value;
        emit dataChanged(indexOf(playerName));
    }
    Q_INVOKABLE void setInGame(const QString &playerName, const bool &value)
    {
        auto m = &model(playerName);
        m->in = value;
        emit dataChanged(indexOf(playerName));
    }
    Q_INVOKABLE int min(const int &index) const
    {
        return _models.at(index).min;
    }
    Q_INVOKABLE double mid(const int &index) const
    {
        return _models.at(index).mid;
    }
    Q_INVOKABLE int max(const int &index) const
    {
        return _models.at(index).max;
    }
    Q_INVOKABLE bool in(const int &index) const
    {
        return _models.at(index).in;
    }
    Q_INVOKABLE int indexOf(const QString &playerName) const
    {
        for (int i = 0; i < _models.count(); ++i) {
            auto name = _models.at(i).playerName;
            if(name == playerName)
                return i;
        }
        return -1;
    }
    Q_INVOKABLE void clear()
    {
        for (auto &model : _models) {
            model.min = 0;
            model.mid = 0;
            model.max = 0;
            model.in = false;
        }
    }
signals:
    void dataChanged(const int &index);
private:
    struct Model{
        QString playerName;
        int min = 0;
        double mid = 0;
        int max = 0;
        bool in = false;
    };
    Model &model(const QString &playerName)
    {
        for (auto &model : _models) {
            if(model.playerName == playerName)
                return model;
        }
        throw "MODEL NOT FOUND";
    }
    QVector<Model> _models;
};
#endif // VERTICALHEADERLABELS_H
