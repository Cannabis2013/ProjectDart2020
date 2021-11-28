#ifndef DARTSIPTSDBCTX_H
#define DARTSIPTSDBCTX_H
#include "DartsModelsContext/TournamentsDbSLAs/dartsdbslas.h"
#include <QMutexLocker>
#include <qmutex.h>
#include <qdebug.h>
#include <QtConcurrent/QtConcurrent>
class DartsIptsDbCtx : public IDbContext<IModel<QUuid>>
{
public:
    DartsIptsDbCtx *add(IModel<QUuid> *model) override;
    IModel<QUuid> *model(const int &index) const override;
    IModel<QUuid>* model(std::function<bool (IModel<QUuid>*)> predFunct) const override;
    QVector<IModel<QUuid>*> models() const override;
    QVector<IModel<QUuid>*> models(std::function<bool (IModel<QUuid> *)> predFunct) const override;
    DartsIptsDbCtx *remove(const int &index) override;
    IDbContext *remove(const QVector<int> &indexes) override;
    int indexOf(IModel<QUuid>* model) const override;
    DartsIptsDbCtx *replace(const int &index, IModel<QUuid> *model) override;
private:
    QVector<IModel<QUuid>*> _models;
    QMutex _mutex;
};
#endif // DARTSSCOREDB_H
