#ifndef IDARTSTOURNAMENTSDB_H
#define IDARTSTOURNAMENTSDB_H

#include <qvector.h>
#include "idbcontext.h"
#include "itournament.h"

class IDartsTournamentsDb :public IDbContext<ITournament>
{
public:
    virtual void add(const ITournament *tournamentModel) override = 0;
    virtual const ITournament *model(const int &index) const override = 0;
    virtual QVector<const ITournament *> models() const override = 0;
    virtual bool remove(const int &index) override = 0;
    virtual int indexOf(const ITournament *tournamentModel) const override = 0;
    virtual void replace(const int &index, const ITournament *tournamentModel) override = 0;
};

#endif // IDARTSTOURNAMENTSDB_H
