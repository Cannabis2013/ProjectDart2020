#ifndef ADDTOURNAMENTTODB_H
#define ADDTOURNAMENTTODB_H

#include <DartsModelsContext/Contracts/Routines/IDartsAddTournament.h>

struct DartsPlayer;
class QJsonArray;
class IDartsTournament;
class QJsonObject;

class AddTournamentToDb : public IDartsAddTournament
{
public:
        typedef QVector<DartsPlayer> Players;
        virtual bool add(const QByteArray &byteArray, const Indexes &indexes, Services *services) override;
private:
        IDartsTournament *createTournamentModel(const QByteArray &byteArray, Services *services);
        void addPlayerDetails(IDartsTournament *tournament, const Indexes &indexes, Services *services);
        Players toPlayerModels(const QByteArray &byteArray, Services *services);
        void addModelToMemory(IDartsTournament *tournament, Services *services);
        bool persistModel(Services *services);
};

#endif // ADDTOURNAMENTTODB_H
