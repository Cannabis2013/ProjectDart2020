#ifndef IDARTSREVEALINPUT_H
#define IDARTSREVEALINPUT_H

class DartsModelsServices;
class QByteArray;
class QString;
class QUuid;
template<typename T> class QVector;

template<typename TModel> class IDartsRevealInput
{
public:
    typedef TModel Model;
    virtual bool display(QUuid tournamentID, QString name, const QByteArray &indexAsByteArray, DartsModelsServices *services) = 0;
};

#endif // IDARTSREVEALINPUT_H
