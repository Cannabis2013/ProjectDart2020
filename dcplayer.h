#ifndef DCPLAYER_H
#define DCPLAYER_H

#include <idcplayer.h>

namespace DCContext{
    class DCPlayer : public IDCPlayer
    {
    public:
        DCPlayer(const QUuid &id, const QString &name):
            _playerId(id), _playerName(name)
        {}
        virtual QUuid playerId() const override
        {
            return _playerId;
        }
        virtual QString playerName() const override
        {
            return _playerName;
        }
    private:
        const QUuid _playerId;
        const QString _playerName = "John Doe";
    };
}
#endif // DCPLAYER_H
