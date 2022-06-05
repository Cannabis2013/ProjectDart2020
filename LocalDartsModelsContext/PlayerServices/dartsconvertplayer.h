#ifndef DARTSCONVERTPLAYER_H
#define DARTSCONVERTPLAYER_H

#include <DartsModelsContext/ForeignContextSLAs/IDartsConvertPlayer.h>

class QString;
class QUuid;

class DartsConvertPlayer : public IDartsConvertPlayer
{
public:
    Player player(const ByteArray &json) const override;
    Player player(const Json &json) const override;
private:
    Json toJsonObject(const ByteArray &byteArray) const;
    Player toPlayer(const Json &json) const;
    QUuid toUuid(const QString &string) const;
};

#endif // DARTSCONVERTPLAYER_H
