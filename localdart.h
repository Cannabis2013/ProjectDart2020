#ifndef PROJECTDART_H
#define PROJECTDART_H

#include "abstractdartinterface.h"
#include "pointlogisticmanager.h"
#include <quuid.h>
#include <qstring.h>
#include <qlist.h>

#define printVariable(var) #var
#define STATUS_ERROR -1;

class LocalDart : public AbstractDartInterface
{
    Q_OBJECT
    // AbstractDartInterface interface
public:
    // public types
    enum GameModes {
        FirstToPost = 0x1,
        RoundBased =0x2,
        CircularDart = 0x3
    };
    enum Status{
        ContextNotInitialized = 0x4,
        ModelNotFound = 0x5,
        NoPlayersAssigned = 0x6,
        Success = 0x7,
        UnSuccess = 0x8
    };
    enum ModelDisplayHint{HiddenHint = 0x1,DisplayHint = 0x2, allHints = 0x4};

    void createInitialModels() const; // For testing purposes

public slots:
    void requestTournaments() override;
    void assignPlayers(const QVariantList &list, const QString &tournament) override;
    void requestPlayerDetails() override;
    void createPlayer(const QString &firstName, const QString &lastName, const QString &email) override;
    void createTournament(const QString &title,
                                         const int &numberOfThrows,
                                         const int &maxPlayers,
                                         const int &gameMode,
                                         const int &keyPoint) override;
    void gameModes() const override;

private slots:
    void forwardScoreFromDataContext(const QUuid &player, const int &score) override;

private :

    int gameModeFromString(const QString &gameMode) const;
    /*
     * Persistence related stuff
     */
    void read();
    void write();
};

#endif // PROJECTDART_H
