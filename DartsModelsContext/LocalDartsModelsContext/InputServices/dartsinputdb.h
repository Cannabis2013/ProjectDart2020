#ifndef DARTSINPUTDB_H
#define DARTSINPUTDB_H

#include <QVector>
#include <DartsModelsContext/Contracts/Db/idbcontext.h>
#include <DartsModelsContext/LocalDartsModelsContext/DbServices/loadfromstorage.h>
#include <DartsModelsContext/LocalDartsModelsContext/DbServices/savetostorage.h>

class QUuid;
template<typename T> class IModel;

class DartsInputDb : public IDbContext<IModel<QUuid>>, public SaveToStorage, public LoadFromStorage
{
public:
    DartsInputDb(const QString &key, IFileDataIO *ioDevice, IModelConverter<IModel<QUuid>> *converter);
    virtual bool saveChanges() override;
    virtual void fetch() override;
    virtual void add(IModel<QUuid> *model) override;
    virtual IModel<QUuid> *model(const int &index) const override;
    virtual IModel<QUuid>* model(std::function<bool (IModel<QUuid>*)> predFunct) const override;
    virtual QVector<IModel<QUuid>*> models() const override;
    virtual QVector<IModel<QUuid>*> models(std::function<bool (IModel<QUuid>*,const int&)> predFunct) const override;
    virtual void remove(const int &index) override;
    virtual void remove(const QVector<int> &indexes) override;
    virtual void remove(std::function<bool (IModel<QUuid>*, const int &)> predFunc) override;
    virtual int indexOf(IModel<QUuid>* model) const override;
    virtual void replace(const int &index, IModel<QUuid> *model) override;
private:
    QVector<IModel<QUuid>*> _models;
};
#endif // DARTSSCOREDB_H
