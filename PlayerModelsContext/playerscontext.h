#ifndef PLAYERSCONTEXT_H
#define PLAYERSCONTEXT_H
#include <QtConcurrent/QtConcurrent>
#include "ContextSLA/absplactx.h"
#ifdef PlaCtxLib
   #define LIB_EXPORT Q_DECL_EXPORT
#else
    #define LIB_EXPORT Q_DECL_IMPORT
#endif
class LIB_EXPORT PlayersContext : public AbsPlaCtx
{
    Q_OBJECT
public:
    Player *player(const QUuid &id) const override;
    Player *player(const QString &name) const override;
    bool createPlayer(const QByteArray &json) override;
    bool remove(const QVector<int> &indexes) override;
    QByteArray players() override;
    Players players(const QVector<int> &indexes) const override;
    Players players(const QVector<QUuid> &ids) const override;
    Players players(const QVector<QString> &names) const override;
};
#endif // PLAYERSCONTEXT_H
