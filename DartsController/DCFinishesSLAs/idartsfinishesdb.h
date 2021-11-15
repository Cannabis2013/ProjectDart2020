#ifndef IDARTSFINISHESDB_H
#define IDARTSFINISHESDB_H
#include <QMultiHash>
#include "ModelsContext/DbSLAs/idbcontext.h"
class IDartsFinishesDb : public IDbContext<QMultiHash<int,QString>>
{
public:
    typedef QMultiHash<int,QString> TargetRows;
    virtual IDartsFinishesDb *add(TargetRows *item) = 0;
    virtual IDartsFinishesDb *add(const QVector<TargetRows*> item) = 0;
    virtual TargetRows *model(const int &index) const = 0;
    virtual TargetRows* model(std::function<bool(TargetRows*)> predFunct) const = 0;
    virtual QVector<TargetRows*> models() const = 0;
    virtual QVector<TargetRows*> models(std::function<bool(TargetRows*)> predFunct) const = 0;
    virtual IDartsFinishesDb *remove(const int &index) = 0;
    virtual int indexOf(TargetRows*) const = 0;
    virtual IDartsFinishesDb *replace(const int &index, TargetRows *model) = 0;
};
#endif // IDARTSSUGGESTIONDB_H
