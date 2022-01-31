#ifndef PLAYERSERVICE_H
#define PLAYERSERVICE_H
#include <QtConcurrent/QtConcurrent>
#include "ContextSLA/absplactx.h"
#ifdef PlaCtxLib
   #define LIB_EXPORT Q_DECL_EXPORT
#else
    #define LIB_EXPORT Q_DECL_IMPORT
#endif
class LIB_EXPORT PlayerService : public AbsPlaCtx
{
    Q_OBJECT
public:
    ByteArray player(const QUuid &id) const override;
    ByteArray player(const QString &name) const override;
    bool createPlayer(const QByteArray &json) override;
    bool remove(const QVector<int> &indexes) override;
    ByteArray players() override;
    ByteArray players(const QVector<int> &indexes) const override;
    ByteArray players(const QVector<QUuid> &ids) const override;
    ByteArray players(const QVector<QString> &names) const override;
};
#endif // PLAYERSCONTEXT_H
