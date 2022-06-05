#ifndef PLAYERSCONTEXT_H
#define PLAYERSCONTEXT_H
#include <QtConcurrent/QtConcurrent>
#include "ContextSLA/abstractplayercontext.h"
#ifdef PlaCtxLib
   #define LIB_EXPORT Q_DECL_EXPORT
#else
    #define LIB_EXPORT Q_DECL_IMPORT
#endif
class LIB_EXPORT PlayersContext : public AbstractPlayerContext
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
