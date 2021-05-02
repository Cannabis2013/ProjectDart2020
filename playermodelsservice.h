#ifndef MODELCONTEXTINTERFACE_H
#define MODELCONTEXTINTERFACE_H

#include <QVariantList>
#include "abstractmodelscontext.h"
#include "localtournamentmodelscontext.h"
#include "localplayermodelscontext.h"
#include "tournamentbuilder.h"
#include "dartsscorebuilder.h"
#include "playermodelbuilder.h"
#include "jsondbcontext.h"
#include "abstractdartsjsonassembler.h"
#include "ibinary.h"
#include "iunary.h"

namespace ModelsContext {
    typedef AbstractDartsJsonAssembler<QByteArray,
                                    ITournamentModelsContext,
                                    IPlayerModelsContext,
                                    QUuid> I501JsonAssembler;
}

class PlayerModelsService : public AbstractModelsContext
{
public:
    /*
     * Public types
     */
    enum TournamentModelsContextResponse{
        TournamentCreatedOK = 0x32,
        TournamentDeletedOK = 0x35,
        EndOfTransmission = 0x10,
        ModelsStatePersisted = 0x47
    };
    enum ModelDisplayHint{
        HiddenHint = 0x1,
        DisplayHint = 0x2,
        allHints = HiddenHint | DisplayHint
    };
    /*
     * Destructor
     *  - Delete contexts to persists changes
     */
    ~PlayerModelsService();
    /*
     * Create instance
     */
    static PlayerModelsService* createInstance();
    ITournamentModelsContext* tournamentModelsContext() const;
    PlayerModelsService *setTournamentModelsContext(ITournamentModelsContext* tournamentModelsContext);

    IPlayerModelsContext* playerModelsContext() const;
    PlayerModelsService *setPlayerModelsContext(IPlayerModelsContext *playerModelsContext);
    ModelsContext::I501JsonAssembler *tournament501JsonAssembler() const;
    void setJsonAssembler(ModelsContext::I501JsonAssembler *jsonAssembler);

public slots:
    /*
     * General tournaments methods
     */
    void assignPlayersToTournament(const QUuid &tournament, const QList<QUuid> &playersID) override;
    void deleteTournaments(const QByteArray &json) override;
    void handleRequestGameMode(const int &index) override;
    void handleRequestTournaments() override;
    void resetTournament(const QUuid &tournament) override;
    /*
     * First To Post tournaments methods
     */
    void addFTPTournament(const QByteArray &json) override;
    void handleRequestFtpScores(const QUuid &tournament) override;
    /*
     * Handle request for 'first To Post'-tournament related meta information
     * from frontend
     *
     * Returned data structure:
     *  - String values are placed in a list of strings
     *  | in the following locations:
     *      [0] = Tournament title
     *      [1] = Tournament winner name
     *  - Numeric values are placed in a list of integers
     *  | in the following locations:
     *      [0] = Tournmaent game mode
     *      [1] = Tournament keypoint
     *      [2] = Tournament model tablehint
     *      [3] = Tournament input mode
     */
    void assembleFtpMetaDataFromId(const QUuid& tournament) override;
    void addDartsPoint(const QByteArray& json) override;
    void set501MultiPointHint(const QUuid &tournament,
                                               const QUuid &player,
                                               const int &roundIndex,
                                               const int &attemptIndex,
                                               const int &hint) override;
    /*
     * Send tournament values
     */
    void assembleFtpKeyValues(const QUuid& tournament) override;
    /*
     * Assemble First To Post tournament indexes and playerscores
     */
    virtual void assembleFtpIndexesAndScores(const QUuid &tournament) override;
    /*
     * Player models context related methods
     */
    void createPlayer(const QByteArray &json) override;
    void deletePlayerFromIndex(const QByteArray& json) override;

    void deletePlayersFromIndexes(const QByteArray& json) override;
    void handleRequestPlayersDetails() override;

private:

    ITournamentModelsContext* _tournamentModelsContext;
    IPlayerModelsContext* _playerModelsContext;
    ModelsContext::I501JsonAssembler* _jsonAssembler;
};

#endif // MODELCONTEXTINTERFACE_H
