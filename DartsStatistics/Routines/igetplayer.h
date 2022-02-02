#ifndef IGETPLAYER_H
#define IGETPLAYER_H
class PlayerStat;
class QString;
class IGetPlayer
{
public:
    virtual PlayerStat get(const QString &name) const = 0;
};

#endif // IGETPLAYER_H
