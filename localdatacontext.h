#ifndef LOCALDATACONTEXT_H
#define LOCALDATACONTEXT_H


#include <quuid.h>
#include <qstring.h>
#include <qlist.h>

#include "abstractpersistence.h"
#include "abstractdatacontext.h"

#include "localplayercontext.h"
#include "tournamentmodelcontext.h"

#define THROW_OBJECT_WITH_ID_NOT_FOUND(x) QString("Model with ID: '%1' does not exists in the current context").arg(x).toStdString();
#define THROW_OBJECT_WITH_INDEX_NOT_FOUND(x) QString("Model with index: '%1' does not exists in the current context").arg(x).toStdString();


class LocalDataContext : public AbstractDataContext,
        private AbstractPersistence
{
    Q_OBJECT
public:
    LocalDataContext(const QString &org, const QString &app);
    /*
     * AbstractPersistence interface
     */
    void read() ;
    void write() ;

    TournamentModelContext *tournamentContext() const;

public slots:
    void sendPlayerScores(const QUuid &tournament) ;
    void appendRound(const QUuid &tournament, const int &index) ;
    void appendSet(const QUuid &tournament, const int &roundIndex, const int &setIndex) ;
    void recieveStatus(const int &status, const QVariantList &args) ;
    void addScore(const QUuid &tournament,
                  const QUuid &player,
                  const int &roundIndex,
                  const int &setIndex,
                  const int &legIndex,
                  const int &point);

private:
    TournamentModelContext *_tournamentContext;
};

#endif // LOCALDATACONTEXT_H
