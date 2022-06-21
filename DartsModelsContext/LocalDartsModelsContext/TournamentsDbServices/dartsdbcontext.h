#ifndef DARTSDBCONTEXT_H
#define DARTSDBCONTEXT_H

#include <quuid.h>
#include <qvector.h>
#include <DartsModelsContext/LocalDartsModelsContext/DbServices/loadfromstorage.h>
#include <DartsModelsContext/LocalDartsModelsContext/DbServices/savetostorage.h>
#include <DartsModelsContext/Contracts/Db/idbcontext.h>

class DartsDbContext :
                public IDbContext<IModel<QUuid>>,
                public SaveToStorage,
                public LoadFromStorage
{
public:
    DartsDbContext(const QString &key, IFileDataIO *ioDevice, IModelConverter<IModel<QUuid>> *converter);
    virtual void add(IModel<QUuid> *model) override;
    virtual IModel<QUuid> *model(const int &index) const override;
    virtual IModel<QUuid>* model(std::function<bool (IModel<QUuid>*)> predFunct) const override;
    virtual QVector<IModel<QUuid>*> models() const override;
    virtual QVector<IModel<QUuid>*> models(std::function<bool (IModel<QUuid>*,const int&)> predFunct) const override;
    virtual void remove(const int &index) override;
    virtual void remove(const QVector<int> &indexes) override;
    virtual void remove(std::function<bool (IModel<QUuid> *, const int &)> predFunc) override;
    virtual int indexOf(IModel<QUuid> *model) const override;
    virtual void replace(const int &index, IModel<QUuid> *model) override;
    virtual bool saveChanges() override;
    virtual void fetch() override;
private:
    IModel<QUuid> *modelByIndex(const int &idx) const;
    QVector<IModel<QUuid>*> _models;
};
#endif // DARTSTOURNAMENTJSONDB_H
