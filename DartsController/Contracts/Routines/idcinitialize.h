#ifndef IDCINITIALIZE_H
#define IDCINITIALIZE_H

struct DCInput;
struct DCPlayer;
struct DCMeta;
class QUuid;
class AbstractDartsContext;

class IDCInitialize {
public:
        virtual int init(const QUuid &tournamentId) = 0;
};
#endif // IDCLOADER_H
