#ifndef IDARTSHIDEINPUT_H
#define IDARTSHIDEINPUT_H

#include <DartsModelsContext/Contracts/dartsmodelsservices.h>
#include <quuid.h>

template<typename TModel> class IDartsHideInput
{
public:
      typedef TModel Model;
      virtual bool hide(QUuid tournamentID, QString name,
                        const QByteArray &indexByteArray,
                        DartsModelsServices *service) = 0;
};

#endif // IDARTSSETIPTHINT_H
