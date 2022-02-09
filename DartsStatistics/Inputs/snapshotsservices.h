#ifndef SNAPSHOTSERVICES_H
#define SNAPSHOTSERVICES_H
#include "icreateinput.h"
#include "ijsontosnapshot.h"
#include "Models/snapshot.h"
#include "Db/istatsdb.h"
class SnapShotsServices
{
public:
    typedef IJsonToSnapShot<SnapShot> JsonToInput;
    typedef IStatsDb<SnapShot> InputsDb;
    typedef ICreateInput<SnapShot> CreateInput;
    JsonToInput *jsonToInput() const {return _jsonToInput;}
    void setJsonToInput(JsonToInput *service) {_jsonToInput = service;}
    InputsDb *snapShots() const {return _inputsDb;}
    void setInputsDb(InputsDb *service) {_inputsDb = service;}
    CreateInput *createSnapShot() const {return _createInput;}
    void setCreateInput(CreateInput *newCreateInput) {_createInput = newCreateInput;}
private:
    JsonToInput *_jsonToInput;
    InputsDb *_inputsDb;
    CreateInput *_createInput;
};
#endif // STATISTICSERVICES_H
