#ifndef LOCALDATACONTEXT_H
#define LOCALDATACONTEXT_H


#include <quuid.h>
#include <qstring.h>
#include <qlist.h>

#include "abstractpersistence.h"
#include "abstractdatacontext.h"

#include "localtournamentmodelcontext.h"
#include "localplayermodelcontext.h"

#define THROW_OBJECT_WITH_ID_NOT_FOUND(x) QString("Model with ID: '%1' does not exists in the current context").arg(x).toStdString();
#define THROW_OBJECT_WITH_INDEX_NOT_FOUND(x) QString("Model with index: '%1' does not exists in the current context").arg(x).toStdString();


class LocalDataContext : public AbstractDataContext,
        private AbstractPersistence
{
    Q_OBJECT
public:
    enum Status{ContextBusy = 0xC, ContextReady = 0xD,ContextSuccessfullyUpdated = 0xE,ContextUnSuccessfullyUpdated = 0xF};
    /*
     * Public types
     */;

    LocalDataContext(const QString &org, const QString &app);

    enum ModelDisplayHint{HiddenHint = 0x1,DisplayHint = 0x2, allHints = 0x4};

    void read()  override;
    void write()  override;

public slots:
    void createTournament(const QString &title,
                          const int &numberOfThrows,
                          const int &maxPlayers,
                          const int &gameMode,
                          const int &keyPoint,
                          const QVariantList &playerIndexes) override;
    void createPlayer(const QString &userName, const QString &mail) override;
    void handleSendPlayerScoresRequest(const QUuid &tournament)  override;
    void updateDataContext(const QUuid &tournament, const int &roundIndex, const int &setIndex) override;
    void appendRound(const QUuid &tournament, const int &index)  override;
    void appendSet(const QUuid &tournament, const int &roundIndex, const int &setIndex)  override;
    void addScore(const QUuid &tournament,
                  const QUuid &player,
                  const int &roundIndex,
                  const int &setIndex,
                  const int &legIndex,
                  const int &point) override;
    void sendRequestedTournaments() override;
    void handleSetCurrentTournament(const int &index) override;
    void handleInitialIndexesRequest(const QUuid &tournament,const QList<QUuid> *assignedPlayers) override;
    void handleSendPlayerDetailsRequest() override;

private:
    void createInitialModels();
};

#endif // LOCALDATACONTEXT_H
