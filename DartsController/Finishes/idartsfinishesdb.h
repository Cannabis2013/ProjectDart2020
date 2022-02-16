#ifndef IDARTSFINISHESDB_H
#define IDARTSFINISHESDB_H
#include <QMultiHash>
class IDartsFinishesDb
{
public:
    typedef QMultiHash<int,QString> TargetRows;
    virtual void add(TargetRows *item) = 0;
    virtual void add(const QVector<TargetRows*> item) = 0;
    virtual TargetRows *model(const int &index) const = 0;
    virtual TargetRows* model(std::function<bool(TargetRows*)> predFunct) const = 0;
    virtual QVector<TargetRows*> models() const = 0;
    virtual QVector<TargetRows*> models(std::function<bool(TargetRows*)> predFunct) const = 0;
    virtual void remove(const int &index) = 0;
    void remove(const QVector<int> &){}
    virtual int indexOf(TargetRows*) const = 0;
    virtual void replace(const int &index, TargetRows *model) = 0;
};
#endif // IDARTSSUGGESTIONDB_H