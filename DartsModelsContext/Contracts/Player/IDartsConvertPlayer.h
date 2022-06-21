#ifndef IDARTSCONVERTPLAYER_H
#define IDARTSCONVERTPLAYER_H
class QJsonObject;
template<typename T> class QVector;
struct DartsPlayer;
class QByteArray;
class IDartsConvertPlayer
{
public:
    typedef QByteArray ByteArray;
    typedef QJsonObject Json;
    typedef DartsPlayer Player;
    typedef QVector<DartsPlayer> Players;
    virtual Player player(const ByteArray &json) const = 0;
    virtual Player player(const Json &json) const = 0;
};

#endif // ICONVERTPLAYER_H