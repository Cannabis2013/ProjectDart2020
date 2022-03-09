#ifndef IDARTSHIDEINPUT_H
#define IDARTSHIDEINPUT_H

class DartsModelsServices;
class QByteArray;
class QString;
class QUuid;
template<typename T> class QVector;

template<typename TModel> class IDartsHideInput
{
public:
    typedef TModel Model;
    virtual bool hide(QUuid tournamentID, QString name, const QByteArray &indexByteArray, DartsModelsServices *service) = 0;
};

#endif // IDARTSSETIPTHINT_H
