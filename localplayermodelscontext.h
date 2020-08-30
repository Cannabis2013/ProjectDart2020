#ifndef LOCALPLAYERCONTEXT_H
#define LOCALPLAYERCONTEXT_H

#include "iplayermodel.h"
#include <quuid.h>
#include <QString>
#include <qlist.h>
#include <qobject.h>
#include "abstractplayermodelscontext.h"
#include "defaultplayerbuilderconfigurations.h"
#include <QVariantList>
#include <iostream>

using namespace std;

namespace PlayerContext {
    class LocalPlayerContext;
    class PlayerModelOptions;
    class PlayerBuilderParameters;
}

typedef IPlayerModel<QUuid,QString> DefaultModelInterface;
typedef IPlayerBuilderParameters<QString,QUuid> DefaultParameters;
typedef IDataModelBuilder<DefaultModelInterface,DefaultParameters,IPlayerBuilderConfiguration> DefaultPlayerBuilder;

class LocalPlayerModelsContext : public AbstractPlayerModelsContext
{
    Q_OBJECT
public:
    /*
     * Public types
     */
    enum ModelsContextResponse{
        PlayerCreatedOK = 0x33,
        PlayerDeletedOK = 0x34,
        PlayersDeletedOK = 0x36
    };
    enum UserRoles{Admin = 0x0, Player = 0x02};

    QList<QUuid> createDummyModels();
    DefaultPlayerBuilder *playerBuilder();
    void setPlayerBuilder(DefaultPlayerBuilder *builder);
public slots:
    void createPlayer(const QString &name, const QString &mail) override;
    void deletePlayer(const int &index) override;
    void deletePlayers(const QVector<int> &playerIndexes) override;
    void assembleListOfPlayersFromIndexes(const QVector<int> &playerIndexes) override;
    void processTournamentDetails(const QUuid &tournament,
                                     const QUuid &winner,
                                     const int &keyPoint,
                                     const int &terminalKeyCode,
                                     const int &numberOfThrows,
                                     const int &gameMode,
                                     const QList<QUuid> &players) override;
    void handleAndProcessTournamentMetaData(const QString &title,
                                            const int &gameMode,
                                            const int &keyPoint,
                                            const QUuid &winnerID,
                                            const QList<QUuid> &assignedPlayersID) override;
    void handleRequestPlayersDetails() override;
    void handleProcessCreatedTournament(const QString &title,
                                        const int &numberOfThrows,
                                        const int &gameMode,
                                        const int &winCondition,
                                        const int &keyPoint,
                                        const QList<int> &playerIndexes) override;
private:
    QUuid createPlayer(const QString &playerName,
                       const QString& email,
                       const int& role) ;
    void deletePlayerByUserName(const QString &firstName) ;
    void deletePlayerByID(const QUuid &player) ;
    void deletePlayerByEmail(const QString &playerEMail) ;
    QUuid playerIDFromName(const QString &fullName) const ;
    QUuid playerIDFromIndex(const int &index) const ;
    QString playerName(const QUuid &id) const ;
    QString playerEMail(const QUuid &id) const ;
    QList<QUuid> players() const ;
    int playersCount() const ;
    DefaultPlayerBuilder *playerBuilder() const;

    void buildPlayerModel(const QUuid &id,
                          const QString &playerName,
                          const QString& email) ;

    DefaultPlayerInterface *getModel(const QString &playerName) const;

    QList<DefaultPlayerInterface*> _models;
    DefaultPlayerBuilder *_playerBuilder;
};

#endif // LOCALPLAYERCONTEXT_H
