#ifndef SNAPSHOTSERVICES_H
#define SNAPSHOTSERVICES_H

#include "icreatesnapshot.h"
#include "Models/snapshot.h"
#include <DartsStatistics/Contracts/Db/istatsdb.h>

class SnapShotsServices
{
public:
    typedef IStatsDb<SnapShot> DbContext;
    typedef ICreateSnapShot<SnapShot> CreateSnapShot;
    DbContext *snapShotsDb() const {return _snapShotsDb;}
    void setSnapShotsDb(DbContext *service) {_snapShotsDb = service;}
    CreateSnapShot *createSnapShot() const {return _createSnapShot;}
    void setCreateSnapShot(CreateSnapShot *newCreateInput) {_createSnapShot = newCreateInput;}
private:
    DbContext *_snapShotsDb;
    CreateSnapShot *_createSnapShot;
};
#endif // STATISTICSERVICES_H
